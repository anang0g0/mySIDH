main(){
  int p=431,i,j,k;

  for(i=0;i<431;i++){
    printf("%d\n",i);
    if((i*i+109*i+225)%p==0){
      printf("d=%d\n",i);
      exit(1);
    }
  }

}
