#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Task 1 from presentation 7
// Modded example from page 407+ in Karpov

// Needed on github?

// NOT DONE

#define LAST_MESSAGE 255

int main(int argc, char *argv[]) {
  int msqid;
  char pathname[]="task_1.c";
  key_t  key;
  int len, maxlen;

  struct mymsgbuf {
     long mtype;
     char mtext[81];
  } mybuf;
    
  key = ftok(pathname, 0);
    
  if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
     printf("Can\'t get msqid\n");
     exit(-1);
  }
    
  while (1) {
      
    maxlen = 81;
       
    if (( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0)) < 0){
      printf("Can\'t receive message from queue\n");
      exit(-1);
    }

    if (mybuf.mtype == LAST_MESSAGE) {
      msgctl(msqid, IPC_RMID, (struct msqid_ds *)NULL);
      exit(0);
    }
       
    printf("message type = %ld, info = %s\n", mybuf.mtype, mybuf.mtext);
  }    

    return 0;
}