#include "krypt.h"

/*
* Used to check if the file is a valid regular file or not.
* Returns non-zero if the file is a regular file.
*/
static int is_regular(const char * filepath)
{
    struct stat path_stat;
    stat(filepath, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

/*
* Lists all files under the directory 'dir' and does the following:
* 1.	Reads the files extensions: 
* 2.	If it contains '.encrypted' it will decrypt the file. The file name of the decrypted
*		file will be the original encrypted filename but without the '.encrypted' extension
* 3.	If it does not contain the named extension it will perform encryption and
*		add the extention to the encrypted file.
*/
void toggle_all_files_in(const char* exe_name, const char* dir, const char* key)
{
	FILE *pr, *fp_r, *fp_w;
	long int sz;
	size_t sz_k;
	int pw, c, i, toggle, crypt=1; //(By default it will presume that encryption is goind to happen)
	char cmd[200], filename[200], filepath[200], riddler, prev_riddler[2], *ch;

	sz_k = strlen(key);

	memset(filename, '\0', sizeof(filename));
	memset(cmd, '\0', sizeof(cmd));
	sprintf(cmd, "ls %s", dir);

	pr = popen(cmd, "r");

	while ( fgets(filename, sizeof(filename) - 1, pr) != NULL ){

		ch = strchr(filename, '\n');
		if ( ch != NULL )
			*ch = '\0';

		if ( strstr(filename, "..") != NULL || strcmp(filename, ".") == 0 
			|| strcmp(filename, exe_name) == 0 || strstr(filename, ".") == NULL ) {
			printf("skipping: %s\n", filename); // These files are not wise to try to modify.
			memset(filename, '\0', sizeof(filename));
			continue;
		}

		memset(filepath, '\0', sizeof(filepath));
		sprintf(filepath, "%s/%s", dir, filename);
		fp_r = fopen(filepath, "r");

		if ( fp_r == NULL ){
			printf("skipping: %s (file can't be opened)\n", filename);
			continue;
		} else if ( !is_regular(filepath) ) {
			printf("skipping: %s (not a regular file)\n", filename);
			fclose(fp_r);
			continue;
		}

		if ( strstr(filename, ".encrypted") != NULL ) {

			crypt=0; // we are decrypting now, not encrypting

			ch = strstr(filename, ".encrypted"); // only decrypt files with names ending at '.encrypted'

			*ch = '\0';
			memset(filepath, '\0', sizeof(filepath));
			sprintf(filepath, "%s/%s", dir, filename);
			*ch = '.';

		} else {
			memset(filepath, '\0', sizeof(filepath));
			sprintf(filepath, "%s/%s.encrypted", dir, filename);	
		}

		fp_w = fopen(filepath, "w");

		fseek(fp_r, 0L, SEEK_END);
		sz = ftell(fp_r);
		fseek(fp_r, 0L, SEEK_SET);

		pw = 0;
		i = 0;
		toggle = 1; 
		prev_riddler[0] = 0;
		prev_riddler[1] = 0;

		while ( (c = fgetc(fp_r)) != EOF ) {

			riddler = key[i % sz_k];

			int pw_c = pw;
			while( pw_c > 0 ){
				riddler *= riddler;
				--pw_c;
			}

			if ( i % 60 == 0 )
				toggle = (pw % 120) > 60 ? -1 : 1;

			if ( i % sz_k == 0 && i > 0 )
				pw += toggle;

			fputc(( crypt == 1 ? c + riddler + prev_riddler[0] + prev_riddler[1]
				: c - riddler - prev_riddler[0] - prev_riddler[1]), fp_w);
			++i;
			prev_riddler[0] = prev_riddler[1];
			prev_riddler[1] = riddler;
		} 

		fclose(fp_w); fclose(fp_r);

		memset(filepath, '\0', sizeof(filepath));
		sprintf(filepath, "%s/%s", dir, filename);
		memset(cmd, '\0', sizeof(cmd));
		sprintf(cmd, "rm \"%s\"", filepath);

		system(cmd); // removing the old unencrypted file

		memset(filename, '\0', sizeof(filename));
	}

	pclose(pr);

}