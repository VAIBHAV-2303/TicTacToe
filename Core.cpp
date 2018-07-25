#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
char board[3][3], maximiser, minimiser;
void print(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}
bool nomovesleft(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]=='_'){
				return false;
			}
		}
	}
	return true;
}
bool wins(char c){
	// Horizontal
	if((board[0][0]==c && board[0][1]==c && board[0][2]==c) || (board[1][0]==c && board[1][1]==c && board[1][2]==c) || (board[2][0]==c && board[2][1]==c && board[2][2]==c)){
		return true;
	}
	// Vertical
	if((board[0][0]==c && board[1][0]==c && board[2][0]==c) || (board[0][1]==c && board[1][1]==c && board[2][1]==c) || (board[0][2]==c && board[1][2]==c && board[2][2]==c)){
		return true;
	}
	// Diagonal
	if((board[0][0]==c && board[1][1]==c && board[2][2]==c) || (board[0][2]==c && board[1][1]==c && board[2][0]==c)){
		return true;
	}
	return false;
}
int minimax(int depth, char c){
	if(wins(maximiser)){
		return 10-depth;
	}
	else if(wins(minimiser)){
		return -10+depth;
	}
	else if(nomovesleft()){
		return 0;
	}

	int curbest;
	if(c==maximiser){
		curbest=-1000;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(board[i][j]=='_'){
					board[i][j]=maximiser;
					if(minimax(depth+1, minimiser)>curbest){
						curbest=minimax(depth+1, minimiser);
					}
					board[i][j]='_';
				}
			}
		}
		return curbest;
	}
	else{
		curbest=1000;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				if(board[i][j]=='_'){
					board[i][j]=minimiser;
					if(minimax(depth+1, maximiser)<curbest){
						curbest=minimax(depth+1, maximiser);
					}
					board[i][j]='_';
				}	
			}
		}
		return curbest;
	}
}
pair<int, int> findmove(){
	pair<int, int> curmove;
	int curbest=-100;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]=='_'){
				// printf("%d %d\n", i, j);
				board[i][j]=maximiser;
				if(minimax(0, minimiser)>curbest){
					curbest=minimax(0, minimiser);
					curmove=make_pair(i, j);
				}
				board[i][j]='_';
			}
		}
	}
	return curmove;
}
int main(){
	printf("Initializing...\n");
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			board[i][j]='_';
		}
	}
	int ch, x, y;
	pair<int, int> bestmove;
	printf("Completed\n\n");
	
	printf("Game Begins\n");
	
// Selecting Turns
	printf("Do you want to go first?\nPress 1 if yes\n0 otherwise\n\n");
	scanf("%d", &ch);
	if(ch){
		maximiser='o';
		minimiser='x';
	}
	else{
		maximiser='x';
		minimiser='o';
		board[0][0]=maximiser;
	}

// Game Loop
	while(true){
		print();
		if(wins(maximiser)){
			printf("I won, You lost!\n");
			break;
		}
		else if(nomovesleft()){
			printf("Boring\n");
			break;
		}
		else{
			printf("Your turn\n\n");
			while(true){
				scanf("%d %d", &x, &y);
				if(board[x][y]=='_'){
					break;
				}
				printf("You're dumb!\n");
			}
			board[x][y]=minimiser;
		}
		print();

		if(wins(minimiser)){
			printf("GG\n");
			break;
		}
		else if(nomovesleft()){
			printf("Boring\n");
			break;
		}
		else{
			printf("My turn\n\n");
			bestmove=findmove();
			board[bestmove.first][bestmove.second]=maximiser;
		}
	}
	return 0;
}
