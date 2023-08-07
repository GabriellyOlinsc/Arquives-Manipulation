#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
typedef struct Nodo{
    string palavra;
    int qtde;
    struct Nodo *prox;
}Tipolista;
typedef struct{
    char palavra[30];
    int qtde;
}Conteudo;

void leituraArquivo(Tipolista **, string);
bool verificaNaLista(Tipolista *lista, string);
void insersaoOrdenadaNaLista(Tipolista **lista,string);
void exibelista(Tipolista *lista);
void destroilista(Tipolista **lista);
void gravaListaEmArqBinario(Tipolista *);
void mostraArquivoBinario();

int main()
{   Tipolista *listaPalavras= NULL;
    string nomeArq;

    cout<<"Informe o nome do arquivo (.txt): ";
    getline(cin,nomeArq);
    leituraArquivo(&listaPalavras,nomeArq);

    system("cls");
    cout<<"Lista encadeada de palavras com 5 ou mais letras: \n"<<endl;
    exibelista(listaPalavras);
    system("PAUSE");
    system("cls");

    gravaListaEmArqBinario(listaPalavras);
    destroilista(&listaPalavras);

    cout<<"Conteudo de lista.bin"<<endl;
    mostraArquivoBinario();
    system("PAUSE");
    system("cls");
    cout<<"Programa Finalizado com sucesso!\nXOXO, Laura e Gaby"<<endl;

    return 0;
}
void gravaListaEmArqBinario(Tipolista *lista){
    Tipolista *p = lista;
    Conteudo registro;

    ofstream arqBin("lista.bin", ios::binary);
    if(arqBin.fail()){
        cout<<"Arquivo binario executado sem sucesso!"<<endl;
        exit(0);
    }
    while(p!=NULL){
        strcpy(registro.palavra,p->palavra.c_str());
        registro.qtde = p-> qtde;
        arqBin.write((const char*)(&registro),sizeof(Conteudo));
        p = p->prox;
    }
    arqBin.close();
}
void mostraArquivoBinario(){
    ifstream arq("lista.bin", ios::binary);
    Conteudo registro;
    if (arq.fail()) {
            cout << "arquivo nao pode ser aberto"; exit(0); }
    arq.seekg(0,ios::end);
    int n = arq.tellg()/sizeof(Conteudo);
    arq.seekg(0,ios::beg);

    for(int i=0;i<n;i++){
        arq.read((char*)(&registro),sizeof(Conteudo));
        cout << "\nPalavra: " << registro.palavra<<endl;
        cout << "Quantidade: " << registro.qtde<< endl;
   }
    arq.close();
}
void leituraArquivo(Tipolista **listaPalavras, string nomeArq){
    string palavra="",linha;
    char ch;

    ifstream arqSeq(nomeArq.c_str());
    if(arqSeq.fail()){
        cout<<"Erro na abertura do arquivo '"<<nomeArq<<"'!";
        exit(0);
    }
     while(arqSeq.get(ch)){
        if(ch == ' ' or ch == '\n'){
            if(palavra.size()>=5){
                if(!(verificaNaLista(*listaPalavras,palavra)))
                    insersaoOrdenadaNaLista(listaPalavras,palavra);
            }
            palavra="";
        }else
            palavra = palavra + ch;
    }
    arqSeq.close();
}
bool verificaNaLista(Tipolista *lista, string palavra){
    Tipolista *paux;
    paux = lista;
    while(paux!= NULL){
        if(paux->palavra == palavra){
            paux->qtde++;
            return true;
        }
        paux=paux->prox;
    }
    return false;
}
void exibelista(Tipolista *lista){
     Tipolista *p = lista;
     while(p != NULL){
        cout<<"Nodo "<<p<<" | Palavra: "<<p->palavra<<" | Frequencia: "<<p->qtde<<"\n"<<endl;
        p = p->prox;
     }
}
void destroilista(Tipolista **ptr_lista) {
     Tipolista *p;
     while(*ptr_lista != NULL){
         p = *ptr_lista;
         *ptr_lista = (*ptr_lista)->prox;
     delete p;
     }
}
void insersaoOrdenadaNaLista(Tipolista **lista, string palavra){
    Tipolista *p, *paux, *pant;
    p = new Tipolista;
    if(p==NULL){
        cout << "Alocacao de memoria sem sucesso!";
        exit(1);
    }
    p->palavra = palavra;
    p->qtde = 1;
    p->prox= NULL;

    if(*lista == NULL){
        *lista = p; return;
    }
    //após insersão do primeiro nodo
    paux = *lista;
    if(palavra < paux->palavra){ //se for o primeiro nodo
        p->prox = paux;
        *lista = p;
    }
    pant = *lista;
    paux = pant;
    if(pant->prox!=NULL){ //se for nulo, vai ser o segundo nodo
        pant = pant -> prox;
        while(pant != NULL) {
            if(palavra < pant->palavra){
                paux->prox = p;
                p->prox = pant;
                return;
            }
            paux = pant;
            pant = pant -> prox;
        }
    }
    paux -> prox = p;
}
