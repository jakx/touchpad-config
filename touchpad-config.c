/*
Jack Daines
Apr 26. 2014
https://github.com/jakx
Dedicated to my baby girl

An app that interprets hand movements on a touchpad laptop

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/prctl.h>
#include <signal.h>


static FILE *fp;


int main( int argc, char *argv[] )
{

  //close all child process
  prctl(PR_SET_PDEATHSIG, SIGHUP);
  int status;
  char buf[1035];

  bool skip = false;
  bool first = true;
  bool start = false;
  int start_x = 0;
  int start_y = 0;
  int diff_x = 0;
  int diff_y = 0;
  double timestart = 0;
  double timeend = 0;
  
  double time = 0;
  int x = 0;
  int y = 0;
  int fingers = 0;
  int prev_fingers = 0;

  /* Open the command for reading. */
  fp = popen("synclient -m 100", "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit;
  }

  /* Read the output a line at a time - output it. */
  while (fgets(buf, sizeof(buf)-1, fp) != NULL) {
        char* token;
        token = (char*)strtok(buf, " ");
        int i = 1;
        time = atof(token);
        while (token) {
            token = (char*)strtok(NULL, " ");


            if(i == 1) x = atoi(token);
            if(i == 2) y = atoi(token);
            if(i == 4) fingers = atoi(token);
            i+= 1;
        }
        if( fingers == 3 || fingers == 4 || fingers == 2){
            if(! start) {
                prev_fingers = fingers;
                start_x = x;
                start_y = y;
                start = true;
                timestart = time; 
            }
       }
       if(start && !(fingers == 3 || fingers == 4 || fingers ==2)){
                if(time - timestart > .38 ){
                    start = false;
                    start_x = 0;
                    start_y = 0;
                    diff_x = 0;
                    diff_y = 0;
                 }
                else {
                    diff_x = x - start_x;
                    diff_y = y - start_y;
                    if(prev_fingers == 4){
                            //up
                            if(diff_y < -200){
                                popen("xdotool key ctrl+alt+d", "re");
                            }
                            //down
                            else if(diff_y > 200){
                                popen("xdotool key super+t", "re");
                            }
                    }
                    if(prev_fingers == 3){
                            //left
                            if(diff_x < -105){
                                  popen("xdotool key alt+Left", "re");
                            }
                            //right
                            else if(diff_x > 105){
                                popen("xdotool key alt+Right", "re");
                            }
                            else if(diff_y < -200){
                                popen("xdotool key ctrl+alt+d", "re");
                            }
                            else if(diff_y > 200){
                                popen("xdotool key super+t", "re");
                            }
                    }
                    
                    start = false;
                    start_x = 0;
                    start_y = 0;
                    diff_y= 0;
                    diff_x= 0;
                }
             }    
          }

  /* close */
  pclose(fp);

  return 0;
 }


