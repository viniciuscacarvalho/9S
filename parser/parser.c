#include "parser.h"


#define MAX_LINE_LEN 64

unsigned char command_len = 0;
command_t* command_list;


callback_pointer get_callback_by_name(const char* name) {
    if (strcmp(name, "RESET") == 0) return reset;
    if (strcmp(name, "SAMPLE") == 0) return sample;
    if (strcmp(name, "SET_SAMPLE_RATE") == 0) return set_sample_rate;
    if (strcmp(name, "CALIBRATE_SENSOR") == 0) return calibrate_sensor;
    if (strcmp(name, "PING_GNSS") == 0) return ping_gnss;
    if (strcmp(name, "PING_MC") == 0) return ping_mc;
    if (strcmp(name, "SHUTDOWN") == 0) return shutdown;
    if (strcmp(name, "WAKEUP") == 0) return wakeup;
    if (strcmp(name, "VERSION") == 0) return version;
    if (strcmp(name, "DEBUG") == 0) return debug;
    return NULL;
}


char* my_strdup(const char* src) {
    if (!src) return NULL;
    size_t len = strlen(src) + 1;
    char* dst = malloc(len);
    if (dst) memcpy(dst, src, len);
    return dst;
}

int init_parser()
{


    FILE* file = fopen("commands.txt", "r");
    if (!file) {
        perror("Failed to open command file");
        return -1;
    }

    
    char line[MAX_LINE_LEN] = {0};
    int count = 0;

    fgets(line, sizeof(line), file);
    sscanf(line, "cmd_len:%hhu", &command_len);
    printf("cmd_len:%d\n",command_len);

    command_list = malloc(command_len * sizeof(command_t));
    if (!command_list) {
        perror("Failed to allocate memory for command_list");
        fclose(file);
        return -1;
    }


    while (fgets(line, sizeof(line), file) && count < command_len) {
        // Pular linhas vazias ou só com \n
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') continue;
    
        // Parse command name    
        //printf("Linha lida: [%s]\n", line);


        // Parse command name
        char cmd_name[MAX_LINE_LEN] = {0}, cb_name[MAX_LINE_LEN] ={0};
        int param_num = 0;

        sscanf(line, "cmd:%s", cmd_name);
        // Read callback line
        if (!fgets(line, sizeof(line), file)) break;
        sscanf(line, "cb:%s", cb_name);

        // Read parameter number line
        if (!fgets(line, sizeof(line), file)) break;
        sscanf(line, "np:%d", &param_num);

        // Store in struct
        command_list[count].command_name = my_strdup(cmd_name);
        command_list[count].command_callback = get_callback_by_name(cb_name);
        command_list[count].parameter_number = (char)param_num;

        count++;

        // Read optional blank line between entries
        fgets(line, sizeof(line), file);
    }

    fclose(file);
    return 0;
}

int parser(char * cmd)
{
    char * temp_cmd;
    char * ptr; 
    for (size_t i = 0; i < command_len; i++)
    {  
        temp_cmd = cmd;
        ptr = command_list[i].command_name;

        printf("\n");
        //printf("%s\n",cmd);
        printf("%s\n",ptr);
        
        while (*temp_cmd == *ptr && *ptr != '\0') {
            temp_cmd++;
            ptr++;
        }
        
        if (*ptr == '\0') {
            printf("Detected!\n");
            command_list[i].command_callback((void*)0);
            printf("Number of parameters:%d\n",command_list[i].parameter_number);
            return PARSER_OK;
        }
    }
    return PARSER_NOT_FOUND;
}


int parser_dinit()
{
    for (int i = 0; i < command_len; i++) {
        free(command_list[i].command_name);
    }
    free(command_list);
}