#include <stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>


struct T_req{
    int id;
    char created_at[51];
    char text[141];
    char user[21];
    struct T_req *next;
};

typedef struct T_req user;

void CreateNewTweet(user **head,char UName[],int *ID_1){
	user *temp = (user*)malloc(sizeof(user));
	temp->id = *ID_1;
	*ID_1 = *ID_1+1;
	temp->next = NULL;
	strcpy(temp->user,UName);
	printf("Enter the tweet :");
	scanf("%[^\n]s",(temp->text));
	if(*head==NULL){
		*head=temp;
	}
	else{
		temp->next=*head;
		*head=temp;
	}
    struct tm *local;
    time_t t;
    t = time(NULL);
    local = gmtime(&t);
    strcpy(temp->created_at,asctime(local));
    strcpy(temp->created_at,strtok(temp->created_at,"\n") );
    printf("New Tweet Created.\n");
    printf("id: %-10d Created at: %s by %s\nTWEET: \"%s\"\n",temp->id,temp->created_at, temp->user,temp->text);
}

int sizeoftweet(user *tweets){
    int count;
    while(tweets!=NULL){
        count++;
        tweets=tweets->next;
    }
    return count;
}

void DisplayTweets(user *head){
	while(head!=NULL){
		printf("ID: %d, \t\t\tCreated at: %s by %s\nTWEET : \"%s\"\n",head->id,head->created_at,head->user,head->text);
		head=head->next;
	}
}


void SearchTweets (user *head, char KeySearch[21]){
	user *current=head;
	int x=0;
	while(current!=NULL){
        if(strstr(current->text, KeySearch) != NULL ){
            printf("Found match:\n");
            printf("ID: %d,\t\t\tCreated at: %s by %s\nTWEET : \"%s\"\n",current->id,current->created_at,current->user, current->text);
            x++;
        }
        current=current->next;
	}
	if(x== 0)
        printf("No tweets matched\n");
	else
		printf(" %d tweets found!\n", x);
}


int SaveTweets(const user *tweets, char *SaveFile){
    int size=sizeoftweet(tweets);
    int c = 0;
    for(int i = 0; i < size; i++){
        if((tweets + i)->id >= 1000 && (tweets + i)->id < 1005){
            c++;
       }
    }
    FILE *fp;
    fp = fopen(SaveFile,"w");
    if(fp != NULL){
        for(int n = 0; n < c; n++){
            fprintf(fp,"%d\n%s\n%s\n%s\n",
            (tweets+n)->id,(tweets+n)->created_at,(tweets+n)->user,(tweets+n)->text);
        }
        fclose(fp);
        printf("%d tweet(s) saved in file \"%s\"",c,SaveFile);
    }
    else{
        printf("There's something wrong with the file");
    }
    return 0;
}

int LoadTweets(user *TWEET, char *filename){
    if(TWEET == NULL){
        printf("Pointing to null\n");
    }
    int size= sizeoftweet(TWEET);
    printf("Size: %d\n", size);
    FILE *fp;
    int count = 0;
    fp = fopen(filename,"r");
    if(fp!=NULL){
        while(!feof(fp)){
            fscanf(fp,"%d%*c",&TWEET[count].id);
            fscanf(fp,"%24[^\n]s",TWEET[count].created_at);
            fscanf(fp,"%*c");
            fscanf(fp,"%20[^\n]s",TWEET[count].user);
            fscanf(fp,"%*c");
            fscanf(fp,"%140[^\n]s",TWEET[count].text);
            count++;
        }
        fclose(fp);
        count--;
        return count;
   }
   else{
        puts("There's something wrong with the file");
        return 0;
   }
}


int main(){
    user *tweet=NULL;
    int i;
    int id = 1000;
    char UName[21];
    char key_search[21];
    char SaveFile[21];
    char LoadFile[21];
    int  c = 0;
    printf(".............twitter.............\n");
    printf("Please enter your name: ");
    scanf("%20[^\n]s", UName);

    printf("Hello, %s \nWelcome to twitter.....! ", UName);
    top:
    printf("\n1. Create a new tweet\n2. Search tweets\n3. Display tweets\n4. Save tweets to file\n5. Load tweets from file\n6. Exit\n");

    printf("\n\nEnter your choice : ");
    scanf("%d",&i);
    getchar();

    while(i!=6){
        switch(i){
            case 1:{
                CreateNewTweet(&tweet, UName,&id);
                id++;
                goto top;
                break;
            }
            case 2:{
                printf("Please enter the search keyword: ");
                scanf("%s", key_search);
                SearchTweets(tweet,key_search);
                goto top;
                break;
            }
            case 3:{
                DisplayTweets(tweet);
                goto top;
                break;
            }
            case 4:{
                printf("Please enter a filename: ");
                scanf("%20[^\n]s%*c", SaveFile);
                SaveTweets(tweet,SaveFile);
                goto top;
                break;
            }
            case 5:{
                printf("Please enter a filename: ");
                scanf("%20[^\n]s%*c", LoadFile);
                c = LoadTweets(tweet,LoadFile);
                id = 1000 + c;
                printf("%d tweet(s) loaded form file \"%s\"",c, LoadFile);
                goto top;
                break;
            }
            case 6:
                break;

            default:
                printf("\nNo Such Function\n");
                goto top;
                break;
        }
    }
    return 0;
}
