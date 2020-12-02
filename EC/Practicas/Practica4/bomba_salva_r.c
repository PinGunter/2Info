// gcc -Og bomba.c -o bomba -no-pie -fno-guess-branch-probability

#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 5


void cifrar(char * inseguro, int desp){
    for (int i=0; i < strlen(inseguro); i++)
        inseguro[i] += desp;
    inseguro[strlen(inseguro)-1] = '\0';    //borramos el \n
}

void explota(){
printf("\033[0;31m");
printf(    
"                 .               \n"
"                 .               \n"
"                 .       :       \n"
"                 :      .        \n"
"        :..   :  : :  .          \n"
"           ..  ; :: .            \n"
"             ... .. :..         \n"
"             ::: :...            \n"
"         ::.:.:...;; .....       \n"
"      :..     .;.. :;     ..     \n"
"            . :. .  ;.           \n"
"             .: ;;: ;.           \n"
"            :; .BRRRV;           \n"
"               YB BMMMBR         \n"
"              ;BVIMMMMMt         \n"
"        .=YRBBBMMMMMMMB          \n"
"      =RMMMMMMMMMMMMMM;          \n"
"    ;BMMR=VMMMMMMMMMMMV.         \n"
"   tMMR::VMMMMMMMMMMMMMB:        \n"
"  tMMt ;BMMMMMMMMMMMMMMMB.       \n"
" ;MMY ;MMMMMMMMMMMMMMMMMMV       \n"
" XMB .BMMMMMMMMMMMMMMMMMMM:      \n"
" BMI +MMMMMMMMMMMMMMMMMMMMi      \n"
".MM= XMMMMMMMMMMMMMMMMMMMMY      \n"
" BMt YMMMMMMMMMMMMMMMMMMMMi      \n"
" VMB +MMMMMMMMMMMMMMMMMMMM:      \n"
" ;MM+ BMMMMMMMMMMMMMMMMMMR       \n"
"  tMBVBMMMMMMMMMMMMMMMMMB.       \n"
"   tMMMMMMMMMMMMMMMMMMMB:        \n"
"    ;BMMMMMMMMMMMMMMMMY          \n"
"      +BMMMMMMMMMMMBY:           \n"
"        :+YRBBBRVt;              \n"
);
exit(0);
}

void desactivar(){
printf("\033[0;34m");
printf(
"         _nnnn_            \n"          
"        dGGGGMMb     ,···························.\n"
"       @p~qp~~qMb    | Has desactivado la bomba! |\n"
"       M|@||@) M|   _;...........................'\n"
"       @,----.JM| -'       \n"
"      JS^\__/  qKL         \n"
"     dZP        qKRb       \n"
"    dZP          qKKb      \n"
"   fZP            SMMb     \n"
"   HZM            MMMM     \n"
"   FqM            MMMM     \n"
" __| '.        |\dS''qML   \n"
" |    `.       | `' \Zq    \n"
"_)      \.___.,|     .'    \n"
"\____   )MMMMMP|   .'      \n"
"     `-'       `--'        \n");

    
exit(0);
}
    


int main(){
    
    //variable con el desplazamiento que se aplicara a la contraseña
    // lo aumentamos con un bucle para que no se pueda averiguar hasta algo avanzado el programa.
    int desp = 0;
    for (int i=0; i <= 9; i++)
        desp++;
    //construimos la contraseña con desplazamiento
    char pass [10]  ={'n'+desp,'o'+desp,'x'+desp,'p'+desp,'l'+desp,'o'+desp,'t'+desp,'a'+desp,'\0'};
    int codigos[4] = { 5, 2, 1, 0};
    codigos[3] = 2*codigos[0] + codigos[1] + codigos[1]*3 +200; //codigo final 218
    char pw[100];
    int pc, n;

    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);

    do printf("Introduce la contraseña: ");
    while (fgets(pw, 100, stdin) == NULL );
    
    cifrar(pw,desp);
    if (strncmp(pw,pass,sizeof(pass)))
        explota();
    
    gettimeofday(&tv2, NULL);
    
    if (tv2.tv_sec - tv1.tv_sec > 60)
        explota();
    do  {
        printf("\nIntroduce el pin: ");
        if ((n=scanf("%i",&pc))==0)
            scanf("%*s")    ==1;         
        
    } while (n!=1 );
    
    if(pc != codigos[3])
        explota();

    gettimeofday(&tv1,NULL);
    if    ( tv1.tv_sec - tv2.tv_sec > 60 )
        explota();

    desactivar();
}



