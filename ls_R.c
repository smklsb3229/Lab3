/* ls_R.c */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define DIR_MAX 20
#define FILE_MAX 100

int line_cnt = -1;

void recursionDir(const char *name) {

	DIR *dir;
	struct dirent *directory;

	char temp[DIR_MAX][FILE_MAX];
	char *directory_path[DIR_MAX];
	int index = 0;
	int p_index = 0;

	for (int i = 0; i < DIR_MAX; i++) {
	       directory_path[i] = NULL;
	       
	       for(int j = 0; j < FILE_MAX; j++) 
		       temp[i][j] = '\0';
	}
	
	if(!(dir = opendir(name)))
		return;

	printf("%s: \n", name);

	while((directory = readdir(dir)) != NULL) {
		if(directory -> d_type == DT_DIR) {
			char path[1024];
			if(strcmp(directory -> d_name, ".") == 0 || strcmp(directory -> d_name, "..") == 0 || strcmp(directory -> d_name, ".git") == 0)
			continue;
			
			snprintf(path, sizeof(path), "%s/%s", name, directory -> d_name);
			for(int k = 0; k < strlen(path); k++)
				temp[index][k] = path[k];

			directory_path[index] = temp[index];
			index++;

			printf("%s\t", directory_path[index - 1]);
		}

		else
			printf("%s\t", directory -> d_name);
		
		line_cnt++;

		if(line_cnt > 5) {
			printf("\n");
			line_cnt = 1;
		}
	}

	printf("\n\n");

	while(directory_path[p_index] != NULL) {
		if(directory_path[p_index] == NULL)
			break;
		recursionDir(directory_path[p_index]);
		p_index++;
	}
	
	closedir(dir);

}

int main(int argc, char *argv[]) {

	char dir[1024];

	if(argc == 1)
		strcpy(dir, ".");
	else
		strcpy(dir, argv[1]);

	recursionDir(dir);
	return 0;
}
