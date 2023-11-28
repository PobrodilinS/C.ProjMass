#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int n(char ***id,char ***name, char ***time,char ***subject,FILE *fp,int q) {
  if (fp==NULL){
    printf("File is not opened\n");
    return 0;
  }
  q=0;
  if ((*id || *name || *time || *subject)){
    for (int i=0;i<q;i++){
      free((*id)[i]);
      free((*name)[i]);
      free((*time)[i]);
      free((*subject)[i]);
    }
    free(*id);
    free(*name);
    free(*time);
    free(*subject);
    *id=NULL;
    *name=NULL;
    *time=NULL;
    *subject=NULL;
  }
  char *token,str[100],*p;
  int counter=0,ids=0,names=0,times=0,subjects=0;
  while(!feof(fp)){
    fgets(str,100,fp);
    q++;
  }
  rewind(fp);
  q=q/5;
  *id=(char**) malloc (q*sizeof(char*));
  *name=(char**) malloc (q*sizeof(char*));
  *time=(char**) malloc (q*sizeof(char*));
  *subject=(char**) malloc (q*sizeof(char*));
  while(!feof(fp)){
  fgets(str,100,fp);
  if (counter==4){
    counter=0;
    continue;
  }
  if (counter==0){
    (*id)[ids]=(char*) malloc ((strlen(str)+1)*sizeof(char));
    if ((*id)[ids]==NULL){printf("ID NIE\n");}
    strcpy((*id)[ids],str);
    (*id)[ids][strcspn((*id)[ids],"\n")+1] = '\0';
    (*id)[ids][strcspn((*id)[ids],"\n")] = ' ';
    ids++;


  }
  if (counter==1){
    (*subject)[subjects]=(char*) malloc ((strlen(str)+1)*sizeof(char));
    if ((*subject)[subjects]==NULL){printf("Subjects NIE\n");}
    strcpy((*subject)[subjects],str);
    (*subject)[subjects][strcspn((*subject)[subjects],"\n")+1] = '\0';
    (*subject)[subjects][strcspn((*subject)[subjects],"\n")] = ' ';
    subjects++;

  }
  if (counter==2){
    (*name)[names]=(char*) malloc ((strlen(str)+1)*sizeof(char));
    if ((*name)[names]==NULL){printf("names NIE\n");}
    for (int i=0;i<strlen(str);i++){
      if(str[i]=='#'){
        str[i]='.';
        str[i+1]='.';
        str[i+2]='.';
      }
    }
    strcpy((*name)[names],str);
    (*name)[names][strcspn((*name)[names],"\n")+1] = '\0';
    (*name)[names][strcspn((*name)[names],"\n")] = ' ';

    names++;

  }
  if (counter==3){
    (*time)[times]=(char*) malloc ((strlen(str)+1)*sizeof(char));
    if ((*time)[times]==NULL){printf("times NIE\n");}
    strcpy((*time)[times],str);
    (*time)[times][strcspn((*time)[times],"\n")+1] = '\0';
    (*time)[times][strcspn((*time)[times],"\n")] = ' ';
    times++;

  }

  counter++;
 }
 rewind(fp);
 return q;
}
int v(char** id, char** name, char** time, char** subject, FILE**fp, int q){
  if(*fp==NULL){
    *fp= fopen("KonferencnyZoznam.txt", "r");
  }
 else{
   fclose(*fp);
   *fp= fopen("KonferencnyZoznam.txt", "r");
 }
  if (*fp==NULL){printf("i couldnt read the document\n");return 0;}
  char c;
  if ((id || name || time || subject)){
    for (int i=0;i<q;i++){
      printf("%s\n",id[i]);
      for(int j=0;j<strlen(name[i]);j++){
        if (name[i][j]!='.'){
          printf("%c",name[i][j]);
        }
        else{
          printf(" ");
        }
      }
      printf("\n");
      printf("%s\n",subject[i]);
      printf("%s\n",time[i]);
      printf("\n");
    }
  }
  else{
    while((c = fgetc(*fp)) != EOF){
        printf("%c",c);
      }
      rewind(*fp);
  }

return 0;
}

int s(char** id, char** name, char** time, char** subject,int q){

  char input[30], dd[3],out[9];
  int in,code=0,size=38;
  char ff[3];
  dd[2]='\0';
  //20200405 UP
  if ((id || name || time || subject)){
  scanf("%d %c%c",&in,&dd[0],&dd[1]);
  for(int i=0;i<q;i++){
    strncpy(out,time[i],8);
    strncpy(ff,id[i],2);
    ff[2]='\0';
    out[8]='\0';
    name[i][strcspn(name[i],"\n")] = 0;

    if (in==atof(out) && strcmp (ff, dd)==0){
      printf("%c%c%c%c   ",time[i][8],time[i][9],time[i][10],time[i][11],name[i],subject[i]);
      for(int j=0;j<strlen(name[i]);j++){
        if (name[i][j]!='.'){
          code=1;
          printf("%c",name[i][j]);
        }
        else{
          printf(" ");
        }
      }
      for(int j=0;j<(size-strlen(name[i]));j++){
        printf(" ");
      }
      printf(" %s\n",subject[i]);
    }
  }
  return code;
  }
  else{
    printf("Arrays are not created\n");
    return 0;
  }
}
int w( char** name,char ***mena, int q){
  int code=0,counter=0,ids=0;
  char *token,na[100];
  if (( name )){
  *mena=(char**) malloc (q*sizeof(char*));

  for (int i=0;i<q;i++){
    strcpy(na,name[i]);
    token = strtok(na, ".");
    while(token!=NULL){
      for (int j=0;j<counter;j++){
        if ((strcmp(token, (*mena)[j])==0)){
          code=1;
          break;
        }
      }
      if (code==0){
        (*mena)[counter]=(char*) malloc ((strlen(token)+1)*sizeof(char));
        strncpy((*mena)[counter],token,strlen(token)+1);
        counter++;
      }
      code=0;
      token=strtok(NULL,".");
      if(strtok(NULL,".")==NULL){
        token=strtok(NULL,".");
      }
    }
  }
  for (int i=0;i<counter;i++){
    for (int j=0;j<strlen((*mena)[i]);j++){
      if ((*mena)[i][j]>='a' && (*mena)[i][j]<='z'){
        (*mena)[i][j]=(*mena)[i][j]-'a'+'A';
      }
    }
  }
  for (int i=0;i<counter;i++){
    printf("%s\n",(*mena)[i]);
  }
}
else{
  printf("Arrays are not created\n");
  return 0;}
}
int p(char ***id,char ***name,char***time,char***subject,int* q){
  char buffer[100]={' '};
  int code=0;
  if(*id || *name || *time || *subject){
    printf("Please enter new id information\n");
    (*q)++;
    buffer[9]=NULL;
    buffer[10]=NULL;
    getchar();
    fgets(buffer,13,stdin);
    if(strlen(buffer)>11){
      printf("Zoznam je nespravny\n");
      (*q)--;
      return 0;
    }
    if(!(buffer[0]=='P' || buffer[0]=='U')){
      printf("Zoznam je nespravny\n");
      (*q)--;
      return 0;
    }
    if(!(buffer[1]=='D' || buffer[1]=='P')){
      printf("Zoznam je nespravny\n");
      (*q)--;
      return 0;
    }
    if(buffer[9]==NULL ){
      printf("Zoznam je nespravny\n");
      (*q)--;
      return 0;
    }
    *id=(char**) realloc (*id,(*q)*sizeof(char*));
    (*id)[(*q)-1]=(char*) malloc ((strlen(buffer)+1)*sizeof(char));
    strncpy((*id)[(*q)-1],buffer,(strlen(buffer)+1));
    (*id)[(*q)-1][strcspn((*id)[(*q)-1],"\n")] = ' ';
    printf("Please enter new subject information\n");
    getchar();

    fgets(buffer,60,stdin);
    *subject=(char**) realloc (*subject,(*q)*sizeof(char*));
    (*subject)[(*q)-1]=(char*) malloc ((strlen(buffer)+1)*sizeof(char));
    strcpy((*subject)[(*q)-1],buffer);
    (*subject)[(*q)-1][strcspn((*subject)[(*q)-1],"\n")] = ' ';

    printf("Please enter new name information\n");

    fgets(buffer,60,stdin);
    for (int i=0;i<strlen(buffer);i++){
      if(buffer[i]=='#'){
        buffer[i]='.';
        buffer[i+1]='.';
        buffer[i+2]='.';
        code=1;
      }
    }
    if(code==0){
      printf("Zoznam je nespravny\n");
      free(*id[(*q)-1]);
      free(*subject[(*q)-1]);
      (*q)--;
      return 0;
    }
    *name=(char**) realloc (*name,(*q)*sizeof(char*));
    (*name)[(*q)-1]=(char*) malloc ((strlen(buffer)+1)*sizeof(char));
    strcpy((*name)[(*q)-1],buffer);
    (*name)[(*q)-1][strcspn((*name)[(*q)-1],"\n")] = ' ';

    printf("Please enter new time information\n");

    fgets(buffer,60,stdin);
    if( atof(buffer)>210000000000 || fmod(atof(buffer),1000)>2000 ||atof(buffer)<200000000000){
      printf("Zoznam je nespravny\n");
      free(*id[(*q)-1]);
      free(*subject[(*q)-1]);
      free(*name[(*q)-1]);
      (*q)--;
      return 0;
    }
    *time=(char**) realloc (*time,(*q)*sizeof(char*));
    (*time)[(*q)-1]=(char*) malloc ((strlen(buffer)+1)*sizeof(char));
    strcpy((*time)[(*q)-1],buffer);
    (*time)[(*q)-1][strcspn((*time)[(*q)-1],"\n")] = ' ';

    printf("Information has been added\n");

  }
  else{
    printf("Please enter new id information\n");
    getchar();

    (*q)++;
    buffer[9]=NULL;
    buffer[11]=NULL;
    fgets(buffer,13,stdin);
    if(strlen(buffer)>11){
      printf("Zoznam je nespravny\n");
      (*q)--;
      return 0;
    }
    if((buffer[0]!='P' && buffer[0]!='U')){
      printf("Zoznam je nespravny \n");
      (*q)--;
      return 0;
    }
    if((buffer[1]!='D' && buffer[1]!='P')){
      printf("Zoznam je nespravny \n");
      (*q)--;
      return 0;
    }
    if(buffer[9]==NULL){
      printf("Zoznam je nespravny \n");
      (*q)--;
      return 0;
    }
    *id=(char**) malloc ((*q)*sizeof(char*));
    (*id)[0]=(char*) malloc ((strlen(buffer)+1)*sizeof(char));
    strncpy((*id)[0],buffer,(strlen(buffer))+1);
    (*id)[0][strcspn((*id)[0],"\n")+1] = '\0';
    (*id)[0][strcspn((*id)[0],"\n")] = ' ';

    printf("Please enter new subject information\n");
    getchar();

    fgets(buffer,60,stdin);
    *subject=(char**) malloc ((*q)*sizeof(char*));
    (*subject)[0]=(char*) malloc ((strlen(buffer)+1)*sizeof(char));
    strcpy((*subject)[0],buffer);
    (*subject)[0][strcspn((*subject)[0],"\n")] = ' ';

    printf("Please enter new name information\n");

    fgets(buffer,60,stdin);
    for (int i=0;i<strlen(buffer);i++){
      if(buffer[i]=='#'){
        buffer[i]='.';
        buffer[i+1]='.';
        buffer[i+2]='.';
        code=1;
      }
    }
    if(code==0){
      printf("Zoznam je nespravny\n");
      free(*id[0]);
      free(*subject[0]);
      (*q)--;
      return 0;
    }
    *name=(char**) malloc ((*q)*sizeof(char*));
    (*name)[0]=(char*) malloc ((strlen(buffer)+1)*sizeof(char));
    strcpy((*name)[0],buffer);
    (*name)[0][strcspn((*name)[0],"\n")] = ' ';

    printf("Please enter new time information\n");

    fgets(buffer,60,stdin);
    if( atof(buffer)>210000000000 || fmod(atof(buffer),1000)>2000 ||atof(buffer)<200000000000){
      printf("Zoznam je nespravny\n");
      free(*id[0]);
      free(*subject[0]);
      free(*name[0]);
      (*q)--;
      return 0;
    }
    *time=(char**) malloc ((*q)*sizeof(char*));
    (*time)[0]=(char*) malloc ((strlen(buffer)+1)*sizeof(char));
    strcpy((*time)[0],buffer);
    (*time)[0][strcspn((*time)[0],"\n")] = ' ';

    printf("Information has been added\n");

  }
  return 0;
}

int d(char ***id,char ***name,char***time,char***subject,int q,char ***mena){
  if(*id || *name || *time || *subject){
    for (int i=0;i<q;i++){
      free((*id)[i]);
      free((*name)[i]);
      free((*time)[i]);
      free((*subject)[i]);
    }
    free(*id);
    free(*name);
    free(*time);
    free(*subject);
    *id=NULL;
    *name=NULL;
    *time=NULL;
    *subject=NULL;
  }
  if (*mena){
    for (int i=0;i<q;i++){
      free((*mena)[i]);
    }
    free(*mena);
    *mena=NULL;
  }
  return 0;
}

void h(char **id, char **time, int q){
  int up[6]={0},ud[6]={0},pp[6]={0},pd[6]={0},counter;
  char is[2];
  double t;
  if(id || time){
    for (int i=0;i<q;i++){
      strncpy(is,id[i],2);
      t=fmod(atof(time[i]),10000);

      for (int j=0;j<6;j++){
        t-=200;
        if(t<800){
          counter=j;
          break;
        }
      }
      if (strcmp (is, "UP")==0){
        up[counter]++;
      }
      if (strcmp (is, "UD")==0){
        ud[counter]++;
      }
      if (strcmp (is, "PP")==0){
        pp[counter]++;
      }
      if (strcmp (is, "PD")==0){
        pd[counter]++;
      }
    }
    printf("   hodina     UP  UD  PP  PD\n");
    printf("8:00 - 9:59   %d   %d   %d   %d\n",up[0],ud[0],pp[0],pd[0]);
    printf("10:00 - 11:59 %d   %d   %d   %d\n",up[1],ud[1],pp[1],pd[1]);
    printf("12:00 - 13:59 %d   %d   %d   %d\n",up[2],ud[2],pp[2],pd[2]);
    printf("14:00 - 15:59 %d   %d   %d   %d\n",up[3],ud[3],pp[3],pd[3]);
    printf("16:00 - 17:59 %d   %d   %d   %d\n",up[4],ud[4],pp[4],pd[4]);
    printf("18:00 - 19:59 %d   %d   %d   %d\n",up[5],ud[5],pp[5],pd[5]);
  }
  else{
    printf("polia nie su vytvoreny\n");
  }

}

int z(char ***id,char ***name,char***time,char***subject,int* q,char* buffer){
  int poz=-1,counter=0,r=0;
  if(*id || *name || *time || *subject){

    for(int i=0;i<(*q);i++){
      if(strcmp(buffer, (*id)[i])==0){
        poz=i;
        counter++;
      }
      if(strcmp(buffer, (*name)[i])==0){
        poz=i;
        counter++;
      }
      if(strcmp(buffer, (*time)[i])==0){
        poz=i;
        counter++;
      }
      if(strcmp(buffer, (*subject)[i])==0){
        poz=i;
        counter++;
      }
    }

    if (poz!=-1){


        for (int i=poz;i<(*q)-1;i++){
          (*id)[i]=(*id)[i+1];
          (*name)[i]=(*name)[i+1];
          (*time)[i]=(*time)[i+1];
          (*subject)[i]=(*subject)[i+1];
          counter=i;
        }

        (*q)--;
        printf("Zoznam zmazen\n");


    }

  }
else{
  printf("Polia nie su vytvoreny\n");
  return -1;
}

return poz;
}

int main(){
  char *token,c[100];
  FILE *fp=NULL;
  int q=0,code,r=0;
  char **id=NULL,**name=NULL,**time=NULL,**subject=NULL,**mena=NULL;
  char zmaz[100];
  while(1){
  scanf("%s",c);
  if(strcmp(c, "n")==0){
    printf("Nacitanie dat\n");
    q=n(&id,&name,&time,&subject,fp,q);

  }
  else if(strcmp(c, "v")==0){
    v(id,name,time,subject,&fp,q);
  }
  else if(strcmp(c, "s")==0){
      printf("Please write YYYYMMDD and ID\n");
      code=s(id,name,time,subject,q);
      if(code==0){
        printf("I didnt found what you are looking for\n");
      }
      while(getchar()!='\n') {
        getchar();
      }
  }
  else if(strcmp(c, "w")==0){
      if(w(name,&mena,q)){
        //n(&id,&name,&time,&subject,fp);
      }

  }
  else if(strcmp(c, "p")==0){
      p(&id,&name,&time,&subject,&q);
  }
  else if(strcmp(c, "z")==0){
    r=0;
    printf("Napiste nazov prispevku\n");
    getchar();
    fgets(zmaz,90,stdin);
    zmaz[strcspn(zmaz,"\n")+1] = '\0';
    zmaz[strcspn(zmaz,"\n")] = ' ';
    while (r!=-1){
      r=z(&id,&name,&time,&subject,&q,zmaz);
    }

  }
  else if(strcmp(c, "h")==0){
    h(id,time,q);
  }
  else if(strcmp(c, "d")==0){
    q=d(&id,&name,&time,&subject,q,&mena);
  }
  else if(strcmp(c, "k")==0){
    fclose(fp);
    fp=NULL;
    q=d(&id,&name,&time,&subject,q,&mena);
  }
  else if(strcmp(c, "x")==0){
    return 0;
  }
  else{
    printf("I couldnt understand you\n");
  }


}
  return 0;

}
