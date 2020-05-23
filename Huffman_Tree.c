#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define SIZE 100
#define Swap_Space 'B' // Cümledeki bosluk sayısının agacta ve listede kolay gorunebilmesi icin yapılan swap islemi 

struct node{
	char charc;
	int freq;
	struct node *left,*right,*next;
};

void Freq(struct node *r,char str[], int i){
	struct node *tmp=r;
	
		while(tmp->next!=NULL){ // linked list içinde elemanımız var mı diye aratıyoruz
			if(str[i]==tmp->charc){ // eğer varsa frekansımız artıyor ve break komutuyla çıkıyoruz
				tmp->freq++;
				break;
			}
			tmp=tmp->next;
		}
		
		if(tmp->next==NULL){ // eğer break ile değil de null olduğu için döngüden çıkıldıysa yeni node eklenecek
			if(tmp->charc==str[i]){ // son elemanı kontrol edemediğimiz için eğer sonuna kadar geldiysek son kontrolümüzü yapıyoruz
				tmp->freq++;
				tmp=tmp->next;
			}
			else{ // eğer yine bulunmadıysa son node a kadar gelip r->next i açıyoruz ve değer eklemeyi gerçekleştiriyoruz
				while(r->next!=NULL)
					r=r->next;
					
					r->next=(struct node*)malloc(sizeof(struct node));
					r->next->charc=str[i];
					r->next->freq=1;
					r->next->next=NULL;
					r->next->left=NULL;
					r->next->right=NULL;
			}
		}
}

void Check_Space(struct node *r){ // Eger Bosluk Tusu varsa bunu Swap_Space de tutulan karakter ile degistiriyoruz agacta ve listede gormemizi kolaylastiriyor.
	struct node *tmp=r;
		while(tmp!=NULL){
			if(tmp->charc==' '){
				tmp->charc = Swap_Space;
				break;
			}
			tmp=tmp->next;
		}
}

struct node* Insertion_Sort(struct node *r){ 
	// 4 farklı liste acarak sıralama algoritmamızı gerceklestiriyoruz
    struct node *sorted, *prev, *ins_ptr, *next; // bunlar bildigimiz prev ve next listesi ayrıyeten sort islemini gerceklestirdigimiz sort ve insertion sort un 2. pointerı olan ins_ptr
	bool flag;
    ins_ptr = r->next; 
    r->next = NULL; 

    while (ins_ptr!=NULL) {
        sorted = r; 
        prev = r;
        next = ins_ptr->next; 

        flag=true;
        while(sorted!=NULL && sorted->freq <= ins_ptr->freq){
            prev = sorted; // sorted pointer ı kucuk oldugu surece liste sonuna kadar prev listesine degerleri atıyoruz
            sorted = sorted->next;
            flag=false;
        }
        	if (sorted!=NULL){ // if sonucuna gore listenin basına veya sonuna ekleme yapıyoruz
        	(flag) ? (r=ins_ptr) : (prev->next=ins_ptr); // Burda flag true ise while dongusune hic girilmemistir r yi kaydırmamız gerekir
			ins_ptr->next = sorted; // degil ise listenin basına degerimizi atıyoruz
        	}
        	else{ 
            ins_ptr->next = NULL;  // ins_ptr buyuk oldugu icin cıktıgımızdan liste sonuna ekleme yapıyoruz
            prev->next = ins_ptr;
        }
        ins_ptr = next; 
    }
    return r;
}

void Make_Tree(struct node *r){
	struct node *index=r, *tmp;
	
	tmp=(struct node*)malloc(sizeof(struct node)); // boş bi temp oluşturup içini dolduruyoruz ardından en sona ekleyip sorting islemi yapıyoruz ki listeyi bozmayacak sekilde eklensin.
	tmp->charc=NULL;
	tmp->freq=(index->freq + index->next->freq);
	
	tmp->left=index;
	tmp->right=index->next;
	index=r;
		
	while(index->next!=NULL)
		index=index->next;
		
	index->next=tmp;
	tmp->next=NULL;
	
	r=Insertion_Sort(r);
}

void Print_Level(struct node* r, int level_no) {
    /* Tree lerdeki klasik dolas fonksiyonu ama aynı seviyedeki nodları aynı anda yazdırabilmek 
	icin level_no kullanarak aynı seviyedeki node ları yukarı kaydırarak aynı anda bastırıyoruz*/
    if (r==NULL){
    	printf("0 ");
    	return;	
	}
    	
    if (level_no == 0) { // en tepedeysek direk basıyoruz
        printf("%d%c ", r->freq,r->charc);
    }
    else {
    	/* sol ve sağ node ları null olana kadar yollayıp uzunlugu 1 azaltarak
    	tepe noktasına ulasmasını saglıyoruz */
        Print_Level(r->left, level_no - 1);
        Print_Level(r->right, level_no - 1);
    }
}

int tree_height(struct node* r){
	// Agacin yuksekligini buluyoruz
		int left, right;
    		if(r==NULL)
        		return;
    /* sol ve sağ agac kısmının uzunlugunu hesaplıyoruz ve hangisi daha uzunsa onu alıyoruz*/
        left = tree_height(r->left);
        right = tree_height(r->right);
        return (left >= right) ? left+1 : right+1;
}

struct node* First_node(char str[]){
	struct node *r;  // ilk node u olusturuyoruz
	r=(struct node*)malloc(sizeof(struct node));
	r->freq=1;
	r->charc=str[0];
	r->next=NULL;
	r->left=NULL;
	r->right=NULL;
	return r;
}

void Print(struct node *r){
	struct node *index=r; // yazdırma işlemi
	
	while(index!=NULL){
		printf("%d%c - ",index->freq,index->charc);
		index=index->next;
	}
	printf("\n");
}

int main(){
	struct node *root;
	char str[SIZE];
	int i;
	
	printf("Yaziyi Giriniz: ");
	scanf("%[^\n]s",str); // Burada normalde strlen fonksiyonu tek kelime sayıyor ama scanf deki duzeltmemiz sayesinde boslukları da sayabiliyoruz
	printf("\n");
	
	root=First_node(str);
	
	for(i=1;i<strlen(str);i++){ // Stringin son elemanı NULL olana kadar ilerliyoruz 
		Freq(root,str,i); // ilk node u oluşturduğumuz için iterasyona 1 den başlıyoruz
	}
	Check_Space(root);
	printf("Your List: ");
	Print(root);
	
	printf("Your Sorted List: ");
	root=Insertion_Sort(root);
	Print(root);

	while(root->next!=NULL){ // Burada her adımda ağacı olusturup rootu kaydırıyoruz
		Make_Tree(root);
		root=root->next->next;
	}
	
	printf("Your Huffmann Tree: \n");
    for (i=0; i<tree_height(root); i++) {
        Print_Level(root, i);
        printf("\n");
    }
    printf("\nNot: %c harfi cumledeki bosluk sayisini, 0 sayisi NULL degerini ifade etmektedir.",Swap_Space);
}
