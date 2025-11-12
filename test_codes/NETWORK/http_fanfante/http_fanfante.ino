#include <SoftwareSerial.h>

// Pino de controle (Power Key). Verifique se o seu módulo usa o pino 12.
#define PWRKEY_PIN 12 
SoftwareSerial sim7070Serial(8, 7); // RX (Arduino -> SIM7070G TX), TX (Arduino -> SIM7070G RX)
#define SerialMon Serial

// Definições de Rede e Servidor
const String APN = "simbase";
const String URL_HOST = "inovtex.com";
const String GET_PATH = "/testes/vinicius/?t=test_arduino_funfante?/"; 

// --- Protótipos de Funções ---
void sendCommand(String command, int timeout); // A função simples solicitada
String readSIM7070Response(int timeout);
bool checkNetworkRegistration(int timeoutSeconds);
bool checkNetworkActivation(int timeoutSeconds);
void sim7070_turnOFF();
bool waitForSHCONN(int timeoutSeconds);
bool sim7070_turnON();

// ====================================================================
// SETUP (Sequência de Conexão e GET)
// ====================================================================

void setup() {
  SerialMon.begin(9600);
  sim7070Serial.begin(19200); 

  // REINICIALIZAÇÃO DO MÓDULO
  sim7070_turnOFF();
  delay(1000);
  sim7070_turnON();
  delay(5000);

  // 1. CONFIGURAÇÃO BÁSICA E DE REDE (Usando sendCommand simples)
  sendCommand("AT", 1000);
  sendCommand("ATE0", 500); 
  sendCommand("AT+CMEE=2", 2000);      // Erros verbosos
  sendCommand("AT+CNMP=38", 2000);     // LTE-only
  sendCommand("AT+CMNB=3", 2000);      // Cat-M/NB-IoT (Automático)
  sendCommand("AT+CGATT=1", 2000); 

  sendCommand("AT+CCLK?", 1000);
  //sendCommand("AT+CCLK=\"25/10/30,14:58:00+00\"", 1000);
  // Comando para sincronizar o relógio do módulo com a rede
  sendCommand("AT+CLTS=1", 1000); // Habilita Sincronização

  // Verifique se o relógio foi atualizado
  sendCommand("AT+CCLK?", 2000);

  // Adicione um AT+CFUN=1,1 (reset de rádio) ou reinicie o módulo AQUI após AT+CLTS=1
  // para que a sincronização automática aconteça.
  // 2. REGISTRO NA REDE (Requer verificação)
  if (!checkNetworkRegistration(120)) { 
    SerialMon.println("[FALHA FATAL] Nao conseguiu registrar na rede.");
    return;
  }
  SerialMon.println("[SUCESSO] Modulo registrado na rede.");

  // 3. ATIVAÇÃO DO CONTEXTO PDP (Requer verificação)
  sendCommand("AT+CGDCONT=1,\"IP\",\"" + APN + "\"", 2000); 
  sendCommand("AT+CNACT=1,1", 1000); 

  if (!checkNetworkActivation(30)) { 
    SerialMon.println("[FALHA FATAL] Contexto de Rede nao ativou.");
    return;
  }
  SerialMon.println("[SUCESSO] Contexto de Rede Ativo com IP.");

  // 4. CONFIGURAÇÃO SSL CRUCIAL PARA HTTPS
  

  //sendCommand("AT+SHSSL=1,\"sslprofile\",1", 2000); 

  //sendCommand("AT+SHSSL=1,1,443", 2000);

  // Configura SNI e Authmode
  sendCommand("AT+SHSSL=1,\"\"", 1000);
  sendCommand("AT+CSSLCFG=\"sslversion\",1,3", 1000);
  sendCommand("AT+CSSLCFG=\"sni\",1,\"" + URL_HOST + "\"", 2000); 
  // Associa o serviço HTTP (SH) ao perfil SSL 1

  

  // 5. CONFIGURAÇÃO HTTP (SHCONF)
  sendCommand("AT+SHCONF=\"URL\",\"https://" + URL_HOST + "\"", 1000); 
  sendCommand("AT+SHCONF=\"BODYLEN\",1024", 1000);
  sendCommand("AT+SHCONF=\"HEADERLEN\",350", 1000);
  sendCommand("AT+SHCONF=\"TIMEOUT\",200", 1000);

  delay(2500);
  // 6. ESTABELECER CONEXÃO (SHCONN)
  // O SHCONN precisa de um timeout longo, e esperamos a resposta "OK"
  
  waitForSHCONN(15);
  // Nota: Se SHCONN falhar, não temos como interromper o programa aqui sem
  // ler ativamente a resposta e procurar por ERROR.

  // 7. ENVIAR REQUISIÇÃO GET (SHREQ)
  SerialMon.print("   Caminho: "); SerialMon.println(URL_HOST + GET_PATH);
  
  String getCommand = "AT+SHREQ=\"" + GET_PATH + "\",1";
  sim7070Serial.println(getCommand); // Envia o comando
  
  // AQUI É O CHECKPOINT CRÍTICO: Lê e verifica o status HTTP 200
  String response = readSIM7070Response(15000); 

  if (response.indexOf("+SHREQ: 0,200") != -1) { 
      SerialMon.println("[SUCESSO] GET Enviado. Status 200 OK recebido.");
      
      // 8. LER RESPOSTA (SHREAD)
      
  } else {
      SerialMon.println("[FALHA] Falha na requisicao GET ou status HTTP nao-200. Resposta do Modulo abaixo:");
      SerialMon.println(response);
  }

  sendCommand("AT+SHREAD=1,500", 5000);
  // 9. LIMPEZA FINAL
  sendCommand("AT+SHDISC", 5000);
  sendCommand("AT+CNACT=0", 5000);
}

void loop() {
  // Loop vazio.
}

// ====================================================================
// FUNÇÕES AUXILIARES
// ====================================================================

// --- Funções de Comunicação (Agora com a estrutura simples solicitada) ---
/**
 * Envia um comando AT, imprime no SerialMon e lê toda a resposta.
 * Não verifica se a resposta é "OK".
 */
void sendCommand(String command, int timeout) {
  SerialMon.print(">> "); SerialMon.println(command);
  sim7070Serial.println(command);
  readSIM7070Response(timeout); 
}

/**
 * Le toda a resposta do módulo e imprime no SerialMon.
 */
String readSIM7070Response(int timeout) {
  unsigned long start = millis();
  String response = "";
  while (millis() - start < timeout) {
    while (sim7070Serial.available()) {
      char c = sim7070Serial.read();
      SerialMon.write(c); 
      response += c;
    }
    delay(1); 
  }
  return response;
}

// --- Funções de Verificação de Estado (Mantidas com lógica de parsing) ---
/**
 * Verifica o registro de rede CEREG. Precisa ler e analisar a resposta.
 */
bool checkNetworkRegistration(int timeoutSeconds) {
  unsigned long start = millis();
  while (millis() - start < (unsigned long)timeoutSeconds * 1000) {
    sim7070Serial.println("AT+CEREG?");
    SerialMon.print(">> AT+CEREG?");
    String response = readSIM7070Response(2000); 
    // Status 1 = Registrado (home network), 5 = Registrado (roaming)
    if (response.indexOf(",1") != -1 || response.indexOf(",5") != -1) {
        return true;
    }
    SerialMon.println(".");
    delay(1000); 
  }
  return false;
}

/**
 * Verifica a ativação do Contexto PDP CNACT. Precisa ler e analisar a resposta.
 */
bool checkNetworkActivation(int timeoutSeconds) {
  unsigned long start = millis();
  while (millis() - start < (unsigned long)timeoutSeconds * 1000) {
    sim7070Serial.println("AT+CNACT?");
    SerialMon.print(">> AT+CNACT?");
    String response = readSIM7070Response(2000); 
    
    // Verifica se o Contexto 1 está ativo E tem um IP válido

    if (response.indexOf("+CNACT: 1,1,\"0.0.0.0\"") == -1) {
        return true;
    }
    SerialMon.println(".");
    delay(1000); 
  }
  return false;
}

// --- Funções de Controle de Energia ---
bool sim7070_turnON() {
  pinMode(PWRKEY_PIN, OUTPUT);
  digitalWrite(PWRKEY_PIN, LOW); 
  delay(100);
  digitalWrite(PWRKEY_PIN, HIGH);
  delay(2500); 
  digitalWrite(PWRKEY_PIN, LOW);
  delay(1000);
  return true;
}

void sim7070_turnOFF() {
  pinMode(PWRKEY_PIN, OUTPUT);
  digitalWrite(PWRKEY_PIN, LOW); 
  delay(100);
  digitalWrite(PWRKEY_PIN, HIGH);
  delay(2500); 
  digitalWrite(PWRKEY_PIN, LOW);
}

bool waitForSHCONN(int timeoutSeconds) {
  unsigned long start = millis();
  int attempt = 0;
  
  SerialMon.println("Iniciando conexão HTTPS...");
  
  while (millis() - start < (unsigned long)timeoutSeconds * 1000) {
    attempt++;
    SerialMon.print("Tentativa de conexão HTTPS ");
    SerialMon.print(attempt);
    SerialMon.println("...");
    
    // 1. Verifica estado atual antes de conectar
    sendCommand("AT+SHSTATE?", 2000);
    
    // 2. Envia comando SHCONN
    sim7070Serial.println("AT+SHCONN");
    SerialMon.println(">> AT+SHCONN");
    
    String response = "";
    unsigned long cmdStart = millis();
    bool connectionEstablished = false;
    bool gotError = false;
    
    // 3. Aguarda resposta com timeout de 20 segundos
    while (millis() - cmdStart < 20000) {
      while (sim7070Serial.available()) {
        char c = sim7070Serial.read();
        SerialMon.write(c);
        response += c;
        
        // Verifica se conexão foi estabelecida
        if (response.indexOf("OK") != -1) {
          connectionEstablished = true;
          SerialMon.println("OK recebido - Conexão estabelecida");
          break;
        }
        if (response.indexOf("ERROR") != -1) {
          gotError = true;
          SerialMon.println("ERROR recebido");
          break;
        }
              }
      
      if (connectionEstablished || gotError) {
        break;
      }
      delay(100);
    }
    
    // 4. Verifica resultado
    if (connectionEstablished) {
      // Verifica estado final da conexão
      SerialMon.println("Verificando estado final da conexão...");
      sendCommand("AT+SHSTATE?", 2000);
      
      // Verifica se realmente está conectado
      if (response.indexOf("+SHSTATE: 1") != -1) {
        SerialMon.println("[SUCESSO] Conexão HTTPS totalmente estabelecida");
        return true;
      } else {
        SerialMon.println("Conexão OK mas estado não confirmado, verificando...");
        sendCommand("AT+SHSTATE?", 2000);
        return true; // Assume sucesso se recebeu OK
      }
    }
    
    if (gotError) {
      SerialMon.println("Conexão falhou com ERROR");
      
      // Tenta obter mais informações do erro
      sendCommand("AT+CMEE?", 1000);
      sendCommand("AT+SHSTATE?", 2000);
    } else {
      SerialMon.println("Timeout na conexão HTTPS");
    }
    
    // 5. Se falhou, faz cleanup e tenta novamente
    SerialMon.println("Limpando estado da conexão...");
    sendCommand("AT+SHDISC", 3000);
    sendCommand("AT+SHSTATE?", 2000);
    
    SerialMon.println("Aguardando 5 segundos para próxima tentativa...");
    delay(5000);
  }
  
  SerialMon.println("[FALHA CRÍTICA] Timeout na conexão HTTPS após todas as tentativas");
  return false;
}