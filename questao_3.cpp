#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct data {// struct para armazenar a validade do produto
    int dia;
    int mes;
    int ano;
};

struct produto { // struct de produto com seus atributos definidos na questão
    int codigo;
    string descricao;
    string marca;
    data data_de_validade; 
    int quantidade;
};

bool organizaEstoque(produto p1, produto p2){//funcao para organizar o estoque por data de validae
    if(p1.codigo!=p2.codigo){//primeiro organizamos por codigo
        return p1.codigo < p2.codigo ;
    }
    if(p1.data_de_validade.ano != p2.data_de_validade.ano){//organizamos por ano
        return p1.data_de_validade.ano < p2.data_de_validade.ano;
    }
    if(p1.data_de_validade.mes != p2.data_de_validade.mes){//organizamos por mes
        return p1.data_de_validade.mes < p2.data_de_validade.mes;
    }

    return p1.data_de_validade.dia < p2.data_de_validade.dia;//por ultimo organizamos por dia
}

bool excluiEstoqueZero(produto p1){
    return (p1.quantidade==0);
}

int menu(){//funcao geral pra mostrar as opcoes ao usuario e receber a resposta
    int opcao;

    cout << "Digite o numero da operacao desejada: " << endl 
    << "0 - Sair" << endl
    << "1 - Relatorio estoque atual" << endl 
    << "2 - Incluir novo produto" << endl 
    << "3 - Retirar produto do estoque" << endl
    << "4 - Consultar produto " << endl;
    
    cin >> opcao;
    
    return opcao;
}

void relatorio(vector< produto > &estoque){//funcao pra mostrar um relatorio do estoque atual
    cout << "RELATORIO DO ESTOQUE ATUAL " << endl;
    cout << "CODIGO        |     DESCRICAO      |        MARCA      | validade    | quantidade" << endl;
    for(int i=0;i < estoque.size();i++){//nao fica alinhado mas mostra tudo
        cout << estoque[i].codigo << "             |   " 
        << estoque[i].descricao   << "   |   "    
        << estoque[i].marca << "   |  " 
        << estoque[i].data_de_validade.dia << '/' << estoque[i].data_de_validade.mes << '/' << estoque[i].data_de_validade.ano << "    |"
        << estoque[i].quantidade << endl;
    }
}

produto incluir(){ // funcao para receber o novo produto para ser adicionado ao estoque
    produto p;
    int cod,qtd;
    string desc,marca;

    cout << "Digite o codigo do produto (Numero Inteiro maior que 0): " << endl;
    while(true){//loop para continuar até o usuario digitar uma entrada valida
        try {
            cin >> cod;
            if (cod<=0) throw -1;//se o usuario digitar um numero negativo disparamos uma exceção
            else break;
        }
        catch (...){
            cout << "digite um numero positivo maior que 0." << endl;
            cin.clear();//comando para limpar o cin da exceção disparada 
            cin.ignore();//limpa o restante da linha para receber nova entrada
        }
    }

    cin.ignore(); //limpa o cin para garantir que não veio lixo da funcao acima

    cout << "Digite a descricao do produto: " << endl;
    getline(cin,desc);

    cout << "Digite a marca do produto: " << endl;
    getline(cin,marca);

    int dia,mes,ano;
    cout << "Digite a data de validade do produto(DD/MM/AAAA): " << endl;
    while(true){//loop para continuar até o usuario digitar uma entrada valida
        try {
            std::cin >> dia;
            std::cin.get();//para pular a / da entrada e pegar só o inteiro
            std::cin >> mes;
            std::cin.get();
            std::cin >> ano;
            if(dia<=0 || mes<=0 || ano<=0 || dia>31 || mes>12 || ano<2000) throw -1;//verificar se a data é valida
            else break;//sair caso a entrada seja valida
        }
        catch (...){
            cout << "Digite uma data valida no formato(DD/MM/AAAA)." << endl;
            cin.clear();//comando para limpar o cin da exceção disparada 
            cin.ignore();//limpa o restante da linha para receber nova entrada
        }
    }



    cout << "Digite a quantidade do produto: " << endl;
    while(true){
        try{
            cin >> qtd;
            if(qtd<=0) throw -1;
            else break;//sair se a entrada for valida
        }catch(...){
            cout << "Digite uma quantidade valida(N positivo maior que zero";
            cin.clear();
            cin.ignore();
        }
    }
    

    p.codigo = cod;
    p.descricao = desc;
    p.marca = marca;
    p.data_de_validade.dia = dia;
    p.data_de_validade.mes = mes;
    p.data_de_validade.ano = ano;

    p.quantidade = qtd;
    
    return p;
}

auto consulta(vector<produto> &estoque){//funcao de consulta um produto pelo codigo, ela retorna um ponteiro pra parte do vetor em que os produtos estão
    int cod;

    cout << "Digite o codigo do produto a ser pesquisado: ";
    try{
        cin >> cod;
        if(cod<=0) throw -1;
    }
    catch(...){
        cout << "Codigo invalido" << endl;
        cod=0;
        cin.clear();//limpar o cin para nova entrada
        cin.ignore();
    }

    auto p = find_if(estoque.begin(),estoque.end(),[cod](const produto& p){//procurar o produto pelo codigo
        return p.codigo == cod;
    });
    if(p != estoque.end()){
        cout << "CODIGO        |     DESCRICAO      |        MARCA      | validade    | quantidade" << endl;
        
        for(int i=0;i<estoque.size();i++){
            if(p[i].codigo!=p[0].codigo) break;
            cout << p[i].codigo << "             |   " 
            << p[i].descricao   << "   |   "    
            << p[i].marca << "   |  " 
            << p[i].data_de_validade.dia << '/' << p[i].data_de_validade.mes << '/' << p[i].data_de_validade.ano << "    |"
            << p[i].quantidade << endl;
        }

    }else{
        cout << "Produto nao encontrado!!! " << endl;
    }

    return p;//retornamos os produtos encontrados para utilizar na funcao de retirar logo abaixo
}

void retirar(auto produto_pesquisado, vector<produto> &estoque){//funcao de retirar produto do estoque
    int retirada;
    cout << "Digite a quantidade de produtos que deseja retirar: ";
    try{
        cin >> retirada;
        if(retirada<=0) throw -1;
    }catch(...){
        cout<<"Quantidade invalida!! " << endl;
        retirada=0;
        cin.clear();//limpar o cin para receber nova entrada
        cin.ignore();
    }
    
    for(int i=0;i<estoque.size();i++){//loop para diminuir o estoque
        
        if(produto_pesquisado[i].codigo!=produto_pesquisado[0].codigo) break;//if de parada
        
        if(retirada >= produto_pesquisado[i].quantidade ){
            retirada-=produto_pesquisado[i].quantidade;
            produto_pesquisado[i].quantidade=0;
        }else{
            produto_pesquisado[i].quantidade-=retirada;
            retirada=0;
            break;
        }
    }
}

int main(){
    vector< produto > estoque; // vetor estoque que vai armazenar os produtos
    int op;

    while(true){

        op = menu();//recebemos a escolha do usuario

        if (op==0) break;//opcao 0 parar o programa

        if(op==1){//opcao 1 relatorio geral do estoque
            relatorio(estoque);
        }

        if (op==2){//opcao 2 é a de incluir novo produto ao estoque
            produto novo_produto = incluir();//funcao de incluir que retorna um novo produto
            estoque.push_back(novo_produto);//adicionar o produto a lista de estoque
            sort(estoque.begin(),estoque.end(),organizaEstoque);
        }
        if (op==3){//opcao 3 é a de retirar produtos do estoque
            auto produto_pesquisado = consulta(estoque);//primeiro chamamos a de consulta para pegar o produto desejado
            
            if(produto_pesquisado != estoque.end()){
                retirar(produto_pesquisado,estoque);//chamamos a de retirar passando o ponteiro dos produtos pesquisados
                
                estoque.erase(remove_if(estoque.begin(),estoque.end(),excluiEstoqueZero),estoque.end());//por fim, apagamos do estoque os produtos com quantidade 0
            }
       }
        if (op==4){//opcao 4 é a de consultar um produto no estoque
            auto nao_utilizado = consulta(estoque);
        }
    }
}