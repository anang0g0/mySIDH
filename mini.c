#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>



typedef struct {
  long long int re;
  long long int im;
} com;

typedef struct {

  com x;
  com y;

} PO;

typedef struct
{
  unsigned int p;
  unsigned int e2;
  unsigned int e3;
  unsigned int xQ20;
  unsigned int xQ21;
  unsigned int yQ20;
  unsigned int yQ21;
  unsigned int xP20;
  unsigned int xP21;
  unsigned int yP20;
  unsigned int yP21;
  unsigned int xR20;
  unsigned int xR21;
  unsigned int xQ30;
  unsigned int xQ31;
  unsigned int yQ30;
  unsigned int yQ31;
  unsigned int xP30;
  unsigned int xP31;
  unsigned int yP30;
  unsigned int yP31;
  unsigned int xR30;
  unsigned int xR31;
  unsigned int n;
} SIDH;

typedef struct
{

  int n;
  int p;
  int q;
  char s[];

} tor;

typedef struct {
  unsigned int p;
  unsigned int e2;
  unsigned int e3;
  PO P2;
  PO P3;
  PO Q2;
  PO Q3;
  PO R2;
  PO R3;
  unsigned int n;
} CM;

unsigned int p=431;
unsigned int pp=185761;




//  SIDH sp434;


// invert of integer
long long int inv(long long int a,long long int n){
  long long int d,x,s,q,r,t;


  d = n;
  x = 0;
  s = 1;
while (a != 0){
    q = d / a;
    r = d % a;
    d = a;
    a = r;
    t = x - q * s;
    x = s;
    s = t;
}
//  gcd = d;  // $\gcd(a, n)$ 

  return ((x + n) % (n / d));
}



//SIDH



com cadd(com a,com b){
  com c;

  c.re=(a.re+b.re);
  if(c.re>p)
    c.re=c.re%p;
  if(c.re<0)
    c.re+=p;
  c.im=(a.im+b.im);
  if(c.im>p)
    c.im=c.im%p;
  if(c.im<0)
    c.im=c.im+p;

  
  return c;
}


com inv_add(com a){// -a
  com c;

  c.re= -1;
  c.im= -1;
  c.re=c.re*a.re%p;
  if(c.re>p)
    c.re%=p;
  c.im=c.im*a.im%p;
  if(c.im>p)
    c.im%=p;
  
  return c;
}

com csub(com a,com b){
  com c,m;

  
  c.re=(a.re-b.re);
  if(c.re<0)
    c.re+=p;
  c.im=(a.im-b.im);
  if(c.im<0)
    c.im+=p;

  
  return c;
}


com cmul(com a,com b){
  com c;
  long long int d,e;
  
  c.re=a.re*b.re-(a.im*b.im);
 
  d=(a.re*b.im);//%p;
  e=(b.re*a.im);//%p;
  //  c.re=c.re+c.im;//%p;
  c.im=d+e;//%p;


  return c;
}


com cinv(com a){
  com c,a1,a2,b1,b2,h,w;
  unsigned int i,j,d,e,f,g,A,pp,l,n;


  for(l=0;l<p;l++){
    //#pragma omp parallel for
    for(n=0;n<p;n++){
      //a=162+172i
      //a2.re=162;
      //a2.im=172;
      a2.re=l; //259
      a2.im=n; //340
      b1=cmul(a2,a);
      if(b1.re%p==1 && b1.im%p==0){
	printf("%d %d %d %d\n",a1.re,a1.im,b1.re%p,b1.im%p);
	printf("%d %d\n",l,n);
	// exit(1);
	return a2;
      }
    }
  }
  
        
  return a2;
}


com cdiv(com a,com b){
  com c,d,v,f,h;
  long long g;
  

  d.re=(b.re*b.re+b.im*b.im)%p;
  if(d.re>p)
    d.re=d.re%p;
  if(d.re<0)
    d.re=d.re+p;
  
  d.im=0;
  
  v.re=((a.re%p)*(b.re%p)+((a.im%p)*(b.im%p))%p)%p;
  v.im=((a.im%p)*(b.re%p))-(a.re%p)*(b.im%p);
    if(a.re>p)
      a.re=a.re%p;
    if(a.re<0)
      a.re=b.re+p;
    if(a.im>p)
      a.im=b.im%p;
    if(a.im<0)
      a.re=a.im+p;

    if(b.re>p)
      b.re=a.re%p;
    if(b.re<0)
      b.re=b.re+p;
    if(b.im>p)
      b.im=b.im%p;
    if(b.im<0)
      b.re=a.im+p;
    
  printf("re=%lld %lld\n",a.re,b.re);
  printf("imm=%lldi %lldi\n",a.im,b.im);
  //exit(1);
  printf("d=%lld\n",d.re);
  d.re=inv(d.re,p);
  
  v.re=((p+v.re)*d.re)%p;
  v.im=((v.im%p)*d.re)%p;
  if(v.re>p)
    v.re=v.re%p;
  if(v.im<0)
    v.im+=p;
  
  printf("v=%lld %lldi\n",v.re,v.im);
  //  exit(1);
  
  //c.re=d.re;
  //c.im=v.im*inv(d.re,p);

  return v;
}


com cnst(unsigned int A,com a){
  unsigned int t,s;
  com r;
  
  t=A*a.re;
  s=A*a.im;
  r.re=t;
  r.im=s;

  return r;
}


PO eadd(PO P,PO Q){
  PO R={0};
  unsigned int r,s,t,u,v,w;
  com c,d,e,f,g,l,A;

  A.re=6;
  A.im=0;
  c=csub(P.y,Q.y);
  d=csub(P.x,Q.x);
  e=cinv(d);
  l=cmul(c,e);
  d=cmul(l,l);
  e=cadd(P.x,Q.x);
  R.x=csub(csub(d,e),A);
  R.y=csub(cmul(l,csub(P.x,R.x)),P.y);


  return R;
}



PO eadd2(PO P){
  com a,b,c;
  PO R;

  
  return R;  
}


//E = EllipticCurve(GF(131), [0, 0, 0, 1, 23])
//E.j_invariant()


com j_inv(com a){
  com r,f,h,b1,b2,h1,o,g,q;
  //  unsigned int w;

  o.re= 3;
  o.im= 0;
  q.re= 256;
  q.im= 0;
  f.re=4;
  f.im=0;
  
  r=cmul(a,a);
  //printf("%d %d\n",r.re,r.im);
  //a^2-4
  h=csub(r,f);
  printf("a^2-4: %lld %lld\n",h.re,h.im);
  b1=cadd(r,f);
  printf("%lld %lld\n",b1.re,b1.im);
  b2=cmul(r,r);
  h1=cmul(f,f);
  h1=cadd(h1,b2);
  printf("%lld %lld\n",h1.re,h1.im);
  
  //p=131 のとき y^2 = x^3 + x + 23 の j-不変量は 78 となります。
  
  //g=a^2-3
  g=csub(r,o);
  printf("a^2-3: %d %d\n",g.re,g.im);
  printf("a^2-4: %lld %lld\n",h.re,h.im);
  //g=256*(a^2-3)^3
  //(a^2 - 3)^2 = -4184900860 - 2323531392 I
  //(a^2 - 3)^3 = 228212128828152 - 239983944473728 I
  
  g=cmul(cmul(cmul(g,g),g),q);
  g.re=g.re%p;
  g.im=g.im%p;
  printf("g=256*(a^2-3)^3: %lld %lld\n",g.re,g.im);
  g=cdiv(g,h);
  if(g.re>p)
    g.re%=p;
  if(g.re<0)
    g.re+=p;
  if(g.im>p)
    g.im=g.im%p;
  if(g.im<0)
    g.im+=p;
  printf("ans=%lld,%lld\n",g.re,g.im);

  
  return g;
}

/*
//jj=aa^bb mod oo
BigInt exp(BigInt aa,BigInt bb,BigInt oo){
  BigInt ii,jj,kk[8192];
  int j,c[8192],count=0,i;

 ii=oo;
  j=0;
  jj=0;
//  kk[4096]; //prime is 4096 bit table
//  c[8192]  //mod is 8192 bit table
  count=0;

  for(i=0;i<8192;i++){
    kk[i]=0;
    }
  while(ii>0){
    ii = (ii>>1);
    j=j+1;
  }


  kk[0]=aa;

//  std::cout << j << "\n";
  
//ex.1000=2**3+2**5+2**6+2**7+2**8+2**9 makes a array c=[3,5,6,7,8,9]
  for(i=0;i<j+1;i++){
    if((bb >> i)%2 != 0){ // testbit(bb,i)
	c[count]=i;
	count=count+1;
      }
    }
//    std::cout << bb << endl;
//    std::cout << count << "\n";
//exit(1);
    for(i=1;i<c[count-1]+1;i++){
      kk[i] = kk[i-1]*kk[i-1]%oo;
    }

    jj=1;
    for(i=0;i<count;i++){
      jj=kk[c[i]]*jj%oo;
      if (jj==0){
//	print i,"\n"
      }
    }

    return jj;
}
*/

com cc(com a,com b){
  com c;

  c.re= a.re*b.re+a.im*b.im;
  c.im=0;
  
  
  return c;
}


int
main ()
{

  char buf[65536];
  CM sp434;
  com a1,a2,b1,b2,j,r,o,q,g,f,v,w,h,r2,g2,h2,h1,c;
  int s=31,t=304,l,k,n,i,count=0,a,b,jj,aa,bb,jj2;

  s=inv(s,p); //a1
  v.re=s;
  v.im=0;
  t=inv(t,p); //a2
  w.re=s;
  w.im=0;
  printf("s=%d,t=%d\n",s,t);
  o.re= 3;
  o.im= 0;
  q.re= 256;
  q.im= 0;
  f.re=4;
  f.im=0;
  
  //h.re=p;
  //h.im=0;
  
  //q=cdiv(r,o);
  //printf("%d %d\n",q.re,q.im);
  //exit(1);

  //a=161+208i
  a1.re=161;
  a1.im=208;

  j_inv(a1);
  printf("a1======================================\n");
  //exit(1);
  
  a2.re=161;
  //162;
  a2.im=208;//172;
  a2=j_inv(a2);

  printf("j=%d %d\n",a2.re,a2.im);
  //exit(1);

  //同じｊ不変量を持つ楕円曲線を総探索する 20200804
  for(i=0;i<p;i++){
    o.re=i;
    for(k=0;k<p;k++){
      o.im=k;
      
      r=j_inv(o);
      //scanf("%d",&n);
      if(r.re==304 && r.im==364){
	printf("(i,k)=%d %d\n",i,k);
	count++;
      }
      /*
      if(i==161 && k==208){
	printf("??\n");
	exit(1);
      }
      */
    }
  }
  printf("p=%d count=%d\n",p,count);

  
  return 0;
}

