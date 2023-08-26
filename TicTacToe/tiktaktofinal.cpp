#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sebagai lambang yang mewakili tiap kotak permainan
char square[20][3] = {"0", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P"};

// berisi string yang akan dipakai di info
struct htp {
  char str[100];
};

int checkwin(); // menentukan kapan dianggap menang
void board(int game); // untuk print papan bermain
void pergerakan(char choice, char mark[]); // mencatat input pemain
void restartsquare(); // testart papan bermain untuk round selanjutnya
void info(struct htp asoy[]); // print cara bermain

int main() {
	struct htp asoy[30];
	
	// menu disimpan di judul.txt
	FILE *fp;
	fp = fopen("judul.txt", "r");
	
	// scan judul dari judul.txt ke stuct Menu Asoy
	int count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%[^\n]\n", asoy[count].str);
		count++;
 	}
	 
	
	int menu;
	do{
		//print menu
		printf("===============================\n");
		printf("Welcome to Three-Way TicTacToe!\n");
    	printf("===============================\n");
		printf("        1. Play Game\n");
    	printf("        2. Exit\n");
    	printf("===============================\n");
    	printf("Please choose a number >> ");
    	scanf("%d", &menu); getchar();
		
		if (menu == 2) { // jika pilih 2
    		printf("***Thanks For Playing!***\n");
    		return 0; // keluar dari permainan
  		} else if (menu < 1 || menu >2) { // jika salah input
    	system("cls");
    	printf("*Invalid Choice\n");
  		}
	}while(menu!=1);
	
	info(asoy);
  
    int countscore[4] = {0}; // menyimpan score pemain ke-i	
    int game = 1; // mewakili round yang sedang dimainkan
    
    // Menang jika ada yang mendapat score 2;
	while (countscore[1] < 2 && countscore[2] < 2 && countscore[3] < 2) { // permainan akan berjalan terus selama belum ada yang menang
    
    int player = 1, i; // player dimulai dari player 1; i sebagai pembantu boolean -> 1 ada yang menang; 0 tidak ada yang menang

    char choice=NULL; // menyimpan opsi yang telah dipilih pemain

    char mark[3]; // menyimpan lambang tiap pemain
    
    do {
        board(game); // print papan bermain
        //penentuan urutan pemain
        if (player % 2 == 0) { // kalau player habis dibagi 2, berarti angka tsb menunjukkan giliran pemain 2
        	player = 2;
		} else if (player % 3 == 0){ // kalau player habis dibagi 3, berarti angka tsb menunjukkan giliran pemain 3
			player = 3;
		} else { // sisanya berarti urutan pemain 1
			player = 1;
		}

    printf("Player %d, enter an alphabet:  ", player);
		
		// penentuan lambang yang akan digunakan tiap pemain
        if (player == 1) {
        	strcpy (mark, "*");
		} else if (player == 2) {
			strcpy (mark, "#");
		} else if (player == 3){
			strcpy (mark, "$");
		}
		
		// proses pemilihan kotak oleh player
		pergerakan(choice, mark);
    	
        i = checkwin(); // menyimpan nilai checkwin untuk menentukan apakah ronde tsb telah selesai
        
		if (player == 3) { // nilai player akan reset lagi bila telah mencapai nilai 3; menghindari kesalahpahaman mis: 4 harusnya player 1 malah jadi player 2 
          player = 1;
        } else player++; // kalau bukan, berarti nilai player ditambah
    } while (i ==  - 1);
    
    board(game); // print papan bermain lagi
        
    if (i == 1) {
    	// Perlu diperhatikan bahwa jumlah player akan +1 dari nilai aslinya karena terjadi player++ di line 99
        if(player==1){ // kalau nilai player = 1; ada 2 kemungkinan
          if(strcmp(mark, "*")==0){
            player=2; // player 1 kalau lambang yang menang adalah '*'
          }else{
            player=4; // player 3
          }
        }
        printf("==>\aPLAYER %d WIN!\n", --player); // print player dengan nilai yang telah dikurangi agar kembali ke nilai asalnya
        countscore[player]++; // menambahkan score dari pemain ke-i yang didapat dari nilai player yang menang
    }else { // kalau tidak ada yang menang:
    	printf("==>\aGAME DRAW\n");
	} 	
    
	//print score sementara
	printf("===================\n");    
    printf("***CURRENT SCORE***\n>Player 1: %d\n>Player 2: %d\n>Player 3: %d\n", countscore[1], countscore[2], countscore[3]);
    printf("Press ENTER to continue\n");
	printf("===================\n");
	getchar();
    restartsquare(); // reset nilai papan menjadi semula
    game++; // ditambah menunjukkan perpindahan ke round selanjutnya
	}
	
	//Penentu pemenang
	int winner;
	for (int i = 1; i <= 3; i++) {
		if (countscore[i] == 2) {
			winner = i;
			break;
		}
	}
	
	printf("=====================================\n");
	printf("\t>>>\aPLAYER %d WINS!<<<\t\n", winner);
	printf("=====================================\n");
	
    return 0;
}


int checkwin() {
	
	/*
	1  = ada kemenangan
	0  = tidak ada kemenangan
	-1 = tidak terjadi apa-apa/ game masih berjalan
	*/
	
	// jika lambang sama semua di:
	if (strcmp(square[1], square[2]) == 0 && strcmp(square[2], square[3]) == 0 && strcmp(square[3], square[4]) == 0) { // horizontal baris A-D
    	return 1;
	} else if (strcmp(square[5], square[6]) == 0 && strcmp(square[6], square[7]) == 0 && strcmp(square[7], square[8]) == 0) { // horizontal baris E-H
    	return 1;
	} else if (strcmp(square[9], square[10]) == 0 && strcmp(square[10], square[11]) == 0 && strcmp(square[11], square[12]) == 0) { // horizontal baris I-L
    	return 1;
	} else if (strcmp(square[13], square[14]) == 0 && strcmp(square[14], square[15]) == 0 && strcmp(square[15], square[16]) == 0) { // horizontal baris M-P
    	return 1;
	} else if (strcmp(square[1], square[5]) == 0 && strcmp(square[5], square[9]) == 0 && strcmp(square[9], square[13]) == 0) { // vertikal kolom A-M
    	return 1;
	} else if (strcmp(square[2], square[6]) == 0 && strcmp(square[6], square[10]) == 0 && strcmp(square[10], square[14]) == 0) { // vertikal kolom B-N
    	return 1;
	} else if (strcmp(square[3], square[7]) == 0 && strcmp(square[7], square[11]) == 0 && strcmp(square[11], square[15]) == 0) { // vertikal kolom C-O
		return 1;
	} else if (strcmp(square[4], square[8]) == 0 && strcmp(square[8], square[12]) == 0 && strcmp(square[12], square[16]) == 0) { // vertikal kolom D-P
		return 1;
	} else if(strcmp(square[1], square[6])==0 && strcmp(square[6], square[11])==0 && strcmp(square[11], square[16])==0) { // diagonakl A-P
  	return 1;
  } else if (strcmp(square[4], square[7])==0 && strcmp(square[7], square[10])==0 && strcmp(square[10], square[13])==0) { // Diagonal D-M
  	return 1;
  } 
  
  // Jika tidak ada yang sama:
  else if 
		(strcmp(square[1], "A") != 0 && strcmp(square[2], "B") != 0 && strcmp(square[3], "C") != 0 
		&& strcmp(square[4], "D") != 0 && strcmp(square[5], "E") != 0 && strcmp(square[6], "F") != 0 
		&& strcmp(square[7], "G") != 0 && strcmp(square[8], "H") != 0 && strcmp(square[9], "I") != 0 
		&& strcmp(square[10], "J") != 0 && strcmp(square[11], "K") != 0 && strcmp(square[12], "L") != 0 
		&& strcmp(square[13], "M") != 0 && strcmp(square[14], "N") != 0 && strcmp(square[15], "O") != 0
		&& strcmp(square[16], "P") != 0) {
			return 0;
		} else {
    	return  - 1;
	}  
}

// Print Papan permainan
void board(int game) {
    system("cls"); // reset tampilan compiler
    printf("\t*********ROUND %d*********", game); // untuk print kita sedang di rount keberapa
    printf("\n\n\t>>>Three-Way TicTacToe<<<\n\n"); // judul

    printf("Player 1 (*)  -  Player 2 (#)  -  Player 3 ($)\n\n\n"); // lambang pemain

	// nilai square didapat dari global variable square
	// nanti nilai dari tiap square dapat berubah jika kotak yang berhubungan dipilih oleh pemain
	
    printf("     |     |     |     \n");
    printf("  %s  |  %s  |  %s  |  %s  \n", square[1], square[2], square[3], square[4]);

    printf("_____|_____|_____|_____\n");
    printf("     |     |     |     \n");

    printf("  %s  |  %s  |  %s  |  %s \n", square[5], square[6], square[7], square[8]);

    printf("_____|_____|_____|_____\n");
    printf("     |     |     |     \n");

    printf("  %s  |  %s  |  %s  |  %s  \n", square[9], square[10], square[11],  square[12]);

    printf("_____|_____|_____|_____\n");
    printf("     |     |     |     \n");

    printf("  %s  |  %s  |  %s  |  %s  \n", square[13], square[14], square[15], square[16]);

    printf("     |     |     |     \n\n");
}

// untuk mencatat gerakan pemain
void pergerakan(char choice, char mark[]) {
	int a=0; // sebagai boolean apakah pergerakan sudah dieksekusi secara benar
	/*
	1 = sudah terjadi proses input dengan benar
	0 = terjadi kesalahan input, jadi pemain harus input lagi atau function pergerakkan harus dieksekusi lagi
	*/
	
  	do{
    	// scan kotak mana yang akan dipilih pemain
		scanf("%c", &choice); getchar();
		
    	// kita typecast jika input dalam bentuk huruf kecil menjadi huruf kapital
    	if (choice >= 'a' && choice <= 'z') {
    		choice -= 32;
		}
    	
    	// pilihan yang tersedia akan menjadikan a sebagai '1'
        if (choice == 'A' && strcmp(square[1], "A") == 0) { // jika pemain pilih kotak A dan kotak tersebut masih kosong
        	strcpy(square[1], mark); a=1;
        	return;
		} else if (choice == 'B' && strcmp(square[2], "B") == 0) { // jika pemain pilih kotak B dan kotak tersebut masih kosong
        	strcpy(square[2], mark);a=1;
        	return;
		} else if (choice == 'C' && strcmp(square[3], "C") == 0) { // jika pemain pilih kotak C dan kotak tersebut masih kosong
        	strcpy(square[3], mark);a=1;
        	return;
		} else if (choice == 'D' && strcmp(square[4], "D") == 0) { // jika pemain pilih kotak D dan kotak tersebut masih kosong
        	strcpy(square[4], mark);a=1;
        	return;
		} else if (choice == 'E' && strcmp(square[5], "E") == 0) { // jika pemain pilih kotak E dan kotak tersebut masih kosong
        	strcpy(square[5], mark);a=1;
        	return;
		} else if (choice == 'F' && strcmp(square[6], "F") == 0) { // jika pemain pilih kotak F dan kotak tersebut masih kosong
        	strcpy(square[6], mark);a=1;
        	return;
		} else if (choice == 'G' && strcmp(square[7], "G") == 0) { // jika pemain pilih kotak G dan kotak tersebut masih kosong
        	strcpy(square[7], mark);a=1;
        	return;
		} else if (choice == 'H' && strcmp(square[8], "H") == 0) { // jika pemain pilih kotak H dan kotak tersebut masih kosong
        	strcpy(square[8], mark);a=1;
        	return;
		} else if (choice == 'I' && strcmp(square[9], "I") == 0) { // jika pemain pilih kotak I dan kotak tersebut masih kosong
        	strcpy(square[9], mark);a=1;
        	return;
		} else if (choice == 'J' && strcmp(square[10], "J") == 0) { // jika pemain pilih kotak J dan kotak tersebut masih kosong
        	strcpy(square[10], mark);a=1;
        	return;
		} else if (choice == 'K' && strcmp(square[11], "K") == 0) { // jika pemain pilih kotak K dan kotak tersebut masih kosong
        	strcpy(square[11], mark);a=1;
			  return;
		} else if (choice == 'L' && strcmp(square[12], "L") == 0) { // jika pemain pilih kotak L dan kotak tersebut masih kosong
        	strcpy(square[12], mark);a=1;
        	return;
		} else if (choice == 'M' && strcmp(square[13], "M") == 0) { // jika pemain pilih kotak M dan kotak tersebut masih kosong
        	strcpy(square[13], mark);a=1;
        	return;
		} else if (choice == 'N' && strcmp(square[14], "N") == 0) { // jika pemain pilih kotak N dan kotak tersebut masih kosong
        	strcpy(square[14], mark);a=1;
        	return;
		} else if (choice == 'O' && strcmp(square[15], "O") == 0) { // jika pemain pilih kotak O dan kotak tersebut masih kosong
        	strcpy(square[15], mark);a=1;
        	return;
		} else if (choice == 'P' && strcmp(square[16], "P") == 0) { // jika pemain pilih kotak P dan kotak tersebut masih kosong
        	strcpy(square[16], mark);a=1;
        	return;
		} else { 
		// jika pilihan sudah dipilih atau bukan pilihan yang tersedia
            printf("Invalid move, enter a alphabet: ");
            choice = 0; // reset ulang nilai choice
        }
  }while(a==0);	
}

// restart nilai
void restartsquare(){
  char j='A'; // index pertama = A, kedua = B, dst...
  for(int i=1; i<18; i++){
    square[i][0] = j;
	j++;
  }
}

void info(struct htp asoy[]) {
	system("cls");
	for (int i = 0; i < 23; i++) {
		printf("%s\n", asoy[i].str);
	}
	getchar();
}
