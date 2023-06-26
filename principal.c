#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define USERS_MAX 1000

typedef struct {
    int id;
    char nome[USERS_MAX];
    char email[USERS_MAX];
    char genero[USERS_MAX];
    char endereco[USERS_MAX];
    double altura;
    int vacinado;
} Usuario;

Usuario usuarios[USERS_MAX];
Usuario usuariosBackup[USERS_MAX];

void main(){
    // Habilitar acentuação
    setlocale(LC_ALL,"");

    printf("----~ Tarefa Vetores e Funções ~----\n");

    // Main loop
    char escolha;
    int ml_flag = 1, invalid_flag;

    while(ml_flag == 1){
        printf("Escolha uma das opções abaixo:\n");
        printf("(0) Finalizar Programa\n");
        printf("(1) Adicionar Usuário\n");
        printf("(2) Editar Usuário\n");
        printf("(3) Excluir Usuário\n");
        printf("(4) Buscar Usuário por e-mail\n");
        printf("(5) Imprimir Todos os Usuários Cadastrados\n");
        printf("(6) Criar Backup dos Usuários\n");
        printf("(7) Restaurar Backup\n> ");
        do{
            invalid_flag = 0;
            scanf(" %c", &escolha);
            switch(escolha){
            case '0':
                printf("Encerrando programa!");
                ml_flag = 0;
                break;
            case '1':
                adicionarUsuario();
                break;
            case '2':
                editarUsuario();
                break;
            case '3':
                removerUsuario();
                break;
            case '4':
                buscarUsuario();
                break;
            case '5':
                imprimirUsuarios();
                break;
            case '6':
                fazerBackup();
                break;
            case '7':
                restaurarBackup();
                break;
            default:
                invalid_flag = 1;
                printf("Escolha Inválida\n> ");
                break;
            }
        }while(invalid_flag == 1);
    }
}

// Funções Principais
void adicionarUsuario(){
    printf(">>> Adicionando Usuário <<<\n");
    float altra;
    int vacinacao;
    getchar();
    for(int i=0; i<3; i++){
        printf("\n");
        usuarios[i].id = gerarID();
        printf("O ID do usuario %d é: %d\n", i, usuarios[i].id);
        
        printf("Digite o nome do usuario %d: ",i);
        fgets(usuarios[i].nome, 100, stdin);
        usuarios[i].nome[strcspn(usuarios[i].nome, "\n")] = '\0';

        printf("Digite o email do usuario %d: ",i);
        fgets(usuarios[i].email, 100, stdin);
        usuarios[i].email[strcspn(usuarios[i].email, "\n")] = '\0';
        while(strchr(usuarios[i].email,'@') == NULL){
            printf("E-mail não é válido, digite um e-mail válido: ");
            fgets(usuarios[i].email, 100, stdin);
            usuarios[i].email[strcspn(usuarios[i].email, "\n")] = '\0';
        }

        printf("Digite o gênero do usuario %d: ",i);
        fgets(usuarios[i].genero, 100, stdin);
        usuarios[i].genero[strcspn(usuarios[i].genero, "\n")] = '\0';
        while(strcmp(usuarios[i].genero,"feminino")!=0 && strcmp(usuarios[i].genero,"masculino")!=0 && strcmp(usuarios[i].genero,"indiferente")!=0){
            printf("Você digitou errado! Digite (feminino, masculino ou indiferente): ",i);
            fgets(usuarios[i].genero, 100, stdin);
            usuarios[i].genero[strcspn(usuarios[i].genero, "\n")] = '\0';
        }

        printf("Digite o endereço do usuario %d: ",i);
        fgets(usuarios[i].endereco, 100, stdin);
        usuarios[i].endereco[strcspn(usuarios[i].endereco, "\n")] = '\0';
        
        printf("Digite a altura do usuario %d: ",i);
        scanf("%f",&altra);
        while (altra < 1 || altra > 2){
            printf("Digite um valor entre 1 e 2 metros: ");
            scanf("%f",&altra);
        };
        usuarios[i].altura = altra;

        printf("Digite (0) se o usuário não for vacinado ou (1) se o usuário for vacinado: ");
        scanf("%i",&vacinacao);
        while(vacinacao!=0 && vacinacao!=1){
            printf("Você digitou errado. Digite (0) se o usuário não for vacinado ou (1) se o usuário for vacinado: ");
            scanf("%i",&vacinacao);
        }
        usuarios[i].vacinado = vacinacao;

        getchar();
    }
}

void editarUsuario(){
    printf(">>> Editando Usuário <<<\n");
    int usuarioEditar, posicao,vacinacao;
    float altra;
    
    printf("Digite o id do usuário que deseja editar: ");
    scanf("%i",&usuarioEditar);
    posicao = posicaoUsuario(usuarioEditar);
    while(posicao == -1){
        printf("Id não existe. Digite um id válido: ");
        scanf("%i",&usuarioEditar);
        posicao = posicaoUsuario(usuarioEditar);
    }
    printf("Usuário encontrado! \n");
    printf("Id: %d\n",usuarios[posicao].id);
    printf("Nome: %s\n",usuarios[posicao].nome);
    printf("E-mail: %s\n",usuarios[posicao].email);
    printf("Gênero: %s\n",usuarios[posicao].genero);
    printf("Endereço: %s\n",usuarios[posicao].endereco);
    printf("Altura: %.2f\n",usuarios[posicao].altura);
    printf("Vacinou: %d\n",usuarios[posicao].vacinado);
    printf("\n");

    getchar();
    printf("Digite o nome do usuario %d: ",posicao);
    fgets(usuarios[posicao].nome, 100, stdin);
    usuarios[posicao].nome[strcspn(usuarios[posicao].nome, "\n")] = '\0';

    printf("Digite o email do usuario %d: ",posicao);
    fgets(usuarios[posicao].email, 100, stdin);
    usuarios[posicao].email[strcspn(usuarios[posicao].email, "\n")] = '\0';
    while(strchr(usuarios[posicao].email,'@') == NULL){
        printf("E-mail não é válido, digite um e-mail válido: ");
        fgets(usuarios[posicao].email, 100, stdin);
        usuarios[posicao].email[strcspn(usuarios[posicao].email, "\n")] = '\0';
    }

    printf("Digite o gênero do usuario %d: ",posicao);
    fgets(usuarios[posicao].genero, 100, stdin);
    usuarios[posicao].genero[strcspn(usuarios[posicao].genero, "\n")] = '\0';
    while(strcmp(usuarios[posicao].genero,"feminino")!=0 && strcmp(usuarios[posicao].genero,"masculino")!=0 && strcmp(usuarios[posicao].genero,"indiferente")!=0){
        printf("Você digitou errado! Digite (feminino, masculino ou indiferente): ",posicao);
        fgets(usuarios[posicao].genero, 100, stdin);
        usuarios[posicao].genero[strcspn(usuarios[posicao].genero, "\n")] = '\0';
    }

    printf("Digite o endereço do usuario %d: ",posicao);
    fgets(usuarios[posicao].endereco, 100, stdin);
    usuarios[posicao].endereco[strcspn(usuarios[posicao].endereco, "\n")] = '\0';
        
    printf("Digite a altura do usuario %d: ",posicao);
    scanf("%f",&altra);
    while (altra < 1 || altra > 2){
        printf("Digite um valor entre 1 e 2 metros: ");
        scanf("%f",&altra);
    };
    
    usuarios[posicao].altura = altra;

    printf("Digite (0) se o usuário não for vacinado ou (1) se o usuário for vacinado: ");
    scanf("%i",&vacinacao);
    while(vacinacao!=0 && vacinacao!=1){
        printf("Você digitou errado. Digite (0) se o usuário não for vacinado ou (1) se o usuário for vacinado: ");
        scanf("%i",&vacinacao);
    }
    usuarios[posicao].vacinado = vacinacao;

    getchar();

}

void removerUsuario(){
    printf(">>> Excluindo Usuário <<<\n");
    int usuarioExcluir, posicao, quantidade;

    printf("Digite o id do usuário que deseja excluir: ");
    scanf("%i",&usuarioExcluir);
    
    posicao = posicaoUsuario(usuarioExcluir);
    while(posicao == -1){
        printf("Id não existe. Digite um id válido: ");
        scanf("%i",&usuarioExcluir);
        posicao = posicaoUsuario(usuarioExcluir);
    }

    quantidade = quantidadeUsuarios();

    for (int i = posicao; i < quantidade - 1; i++) {
        usuarios[i].id = usuarios[i+1].id;
        strncpy(usuarios[i].nome, usuarios[i+1].nome, 100);
        strncpy(usuarios[i].email, usuarios[i+1].email, 100);
        strncpy(usuarios[i].genero, usuarios[i+1].genero, 100);
        strncpy(usuarios[i].endereco, usuarios[i+1].endereco, 100);
        usuarios[i].altura = usuarios[i+1].altura;
        usuarios[i].vacinado = usuarios[i+1].vacinado;
    }

    usuarios[quantidade - 1].id = -1;
    strcpy(usuarios[quantidade - 1].nome, "");
    strcpy(usuarios[quantidade - 1].email, "");
    strcpy(usuarios[quantidade - 1].genero, "");
    strcpy(usuarios[quantidade - 1].endereco, "");
    usuarios[quantidade - 1].altura = -1;
    usuarios[quantidade - 1].vacinado = -1;

    printf(">>> Usuário excluído com sucesso <<<\n");
}

void buscarUsuario(){
    printf(">>> Buscando Usuário <<<\n");
    int quantidade, posicao;
    char usuarioBuscar[100];
    int k=0;

    quantidade = quantidadeUsuarios();
    
    getchar();
    printf("Digite o e-mail do usuário que deseja encontrar as informações: ");
    fgets(usuarioBuscar, 100, stdin);

    while(strchr(usuarioBuscar,'@') == NULL){
        printf("Digitação inválida! Digite um e-mail válido: ");
        fgets(usuarioBuscar, 100, stdin);
        usuarioBuscar[strcspn(usuarioBuscar, "\n")] = '\0';
    }

    usuarioBuscar[strcspn(usuarioBuscar, "\n")] = '\0';

    while(k<quantidade){
        if(strcmp(usuarioBuscar, usuarios[k].email) == 0){
            posicao = k;
            quantidade = k;
        } else{
            posicao = -1;
        }
        k++;
    }

    if (posicao>=0){
        printf("Usuário encontrado! \n");
        printf("Id: %d\n",usuarios[posicao].id);
        printf("Nome: %s\n",usuarios[posicao].nome);
        printf("E-mail: %s\n",usuarios[posicao].email);
        printf("Gênero: %s\n",usuarios[posicao].genero);
        printf("Endereço: %s\n",usuarios[posicao].endereco);
        printf("Altura: %.2f\n",usuarios[posicao].altura);
        printf("Vacinou: %d\n",usuarios[posicao].vacinado);
        printf("\n");
    } else{
        printf("Usuário não encontrado! \n");
    }    
}

void imprimirUsuarios(){
    printf(">>> Imprimindo Todos os Usuários <<<\n");
    for(int i=0; i<quantidadeUsuarios();i++){
        printf("Id: %d\n",usuarios[i].id);
        printf("Nome: %s\n",usuarios[i].nome);
        printf("E-mail: %s\n",usuarios[i].email);
        printf("Gênero: %s\n",usuarios[i].genero);
        printf("Endereço: %s\n",usuarios[i].endereco);
        printf("Altura: %.2f\n",usuarios[i].altura);
        printf("Vacinou: %d\n",usuarios[i].vacinado);
        printf("\n");
    }
}

void fazerBackup(){
    printf(">>> Criando Backup <<<\n");
    int quantidade = quantidadeUsuarios();
    
    for (int i = 0; i < quantidade; i++) {
        usuariosBackup[i].id = usuarios[i].id;
        strcpy(usuariosBackup[i].nome, usuarios[i].nome);
        strcpy(usuariosBackup[i].email, usuarios[i].email);
        strcpy(usuariosBackup[i].genero, usuarios[i].genero);
        strcpy(usuariosBackup[i].endereco, usuarios[i].endereco);
        usuariosBackup[i].altura = usuarios[i].altura;
        usuariosBackup[i].vacinado = usuarios[i].vacinado;
    }

    printf("Backup feito com sucesso!\n");
}

void restaurarBackup(){
    printf(">>> Restaurando Backup <<<\n");
    int quantidade = quantidadeUsuariosBackup();

    for (int i = 0; i < quantidade; i++) {
        usuarios[i].id = usuariosBackup[i].id;
        strcpy(usuarios[i].nome, usuariosBackup[i].nome);
        strcpy(usuarios[i].email, usuariosBackup[i].email);
        strcpy(usuarios[i].genero, usuariosBackup[i].genero);
        strcpy(usuarios[i].endereco, usuariosBackup[i].endereco);
        usuarios[i].altura = usuariosBackup[i].altura;
        usuarios[i].vacinado = usuariosBackup[i].vacinado;
    }

    printf("Restauração concluída com sucesso!\n");
}

// Funções Utilitárias
int gerarID(){
    int gerarID = rand();
    return gerarID;
}

int quantidadeUsuarios(){
    int contador = 0;
    for(int j=0;j<1000;j++){
        if(usuarios[j].id>=1){
            contador++;
        } else{
            return contador;
        }
    }
}

int quantidadeUsuariosBackup(){
    int contador = 0;
    for(int j=0;j<1000;j++){
        if(usuarios[j].id>=1){
            contador++;
        } else{
            return contador;
        }
    }
}

int posicaoUsuario(int idUsuario){
    int quantidade = quantidadeUsuarios();
    for(int i = 0; i<quantidade; i++){
        if(usuarios[i].id == idUsuario){
            return i;
        }
    }
    return -1;
}