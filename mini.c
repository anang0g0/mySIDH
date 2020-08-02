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

//p=131 のとき y^2 = x^3 + x + 23 の j-不変量は 78 となります。


//  SIDH sp434;


// invert of integer
unsigned int inv(unsigned int a,unsigned int n){
  unsigned int d,x,s,q,r,t;


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
  c.im=(a.im+b.im);
  c.re=c.re;
  c.im=c.im;

  return c;
}


com inv_add(com a){// -a
  com c;

  c.re= -1;
  c.im= -1;
  c.re=c.re*a.re%p;
  c.im=c.im*a.im%p;
  
  return c;
}

com csub(com a,com b){
  com c;

  c.re=(a.re-b.re);
  c.im=(a.im-b.im);
    
  return c;
}


com cmul(com a,com b){
  com c;
  long long int d,e;
  
  c.re=a.re*b.re;//%p;
  c.re+= -1*(a.im*b.im);//%p;
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
      

  
  /*    
  A=-1;
  d=a.re*a.re;
  e=a.im*a.im;
  f=(d+e);
  g=inv(f,p);
  d=a.re*g%p;
  f=a.im*A%p;
  e=f*g%p;
  // unsigned int_mul(g,e,f);
  c.re=d;
  c.im=e;
  */
     
      
      //  return;
}


com cdiv(com a,com b){
  com c,d,v,f,h;
  

  d.re=b.re*b.re+b.im*b.im;
  d.im=0;
  
  v.re=a.re*b.re+a.im*b.im;
  v.im=(a.im*b.re-a.re*b.im);
  //f=cinv(d);
  //f.im=0;
  printf("d=%d %di\n",d.re%p,d.im);
  d=cinv(d);
  //d.im=0;
  //v=(v,d);
  printf("v=%d %di\n",v.re%p,v.im%p);
  exit(1);
  
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



PO eadd2(PO P,PO Q){
  com a,b,c;
  PO R;

  
}


//E = EllipticCurve(GF(131), [0, 0, 0, 1, 23])
//E.j_invariant()

  com j_inv(com a){
  com x,y,z,u,v,w;
  //  unsigned int w;
  
  u.re=3;
  u.im=0;
  v.re=4;
  v.im=0;
  w.re=256;
  w.im=0;
  x=csub(cmul(a,a),u);
  x=cmul(cmul(x,x),x);
  x=cmul(w,x);
  y=csub(cmul(a,a),v);
  z=cdiv(x,y);

  
  return z;
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

int
main ()
{

  char buf[65536];
  CM sp434;
  com a1,a2,b1,b2,j,r,o,q,g,f,v,w,h,r2,g2,h2,h1;
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

  /*
(-3+a^2))
-17346 + 66976 I

256 (-3 + a^2)^3
58422304980006912 - 61435889785274368 I
-4 + a^2
-17347 + 66976 I
256 (-3 + a^2)^3 / (-4 + a^2)
- (5128181878746715973632/4786702985) - (2847163918235788476416 I)/4786702985
  */
  
  //b1=cinv(a1);
  //b2=cmul(a1,b1);
  //printf("%d %d\n",b2.re%p,b2.im%p);

  //exit(1);
  
  
  //r=a*a
  r=cmul(a1,a1);
  //printf("%d %d\n",r.re,r.im);
  //a^2-4
  h=csub(r,f);
  //  b2=cinv(h);
  //b2=cmul(b2,h);
  printf("cimv(h)=%d %d\n",h.re,h.im);
  //  exit(1);

  //g=a^2-3
  g=csub(r,o);
  printf("a^2-3: %d %d\n",g.re,g.im);
  //exit(1);
  //g=256*(a^2-3)^3

  //g=cmul(cmul(cmul(g,g),g),q);
  g=cmul(g,g);
  //g=cdiv(g,h);
  //  g=cmul(g,b2);
  printf("g=256*(a^2-3)^3/(a^2-4): %d %d\n",g.re,g.im);
  //exit(1);
  
  //a=162+172i
  //a2.re=162;
  //a2.im=172;
  /*
      a2.re=l; //259
      a2.im=n; //340
      a2=cinv(a1);
  b1=cmul(a2,a1);
  if(b1.re%p==1 && b1.im%p==0){
    printf("%d %d %d %d\n",a2.re,a2.im,b1.re%p,b1.im%p);
    printf("%d %d\n",l,n);
    // exit(1);
  }
  */



  //exit(1);
  //r=a*a
  r2=cmul(a2,a2);
  aa=4*l*l*l%p;
  bb=(aa+27*n*n)%p;
  jj2=aa*inv(bb,p)%p;
  //printf("%d %d\n",r2.re,r2.im);
  //a^2-4
  h1=csub(r2,f);
  h2=cinv(h2);
  //g=a^2-3
  g2=csub(r2,o);
  //printf("a^2-3: %d %d\n",g2.re,g2.im);
  //g=256*(a^2-3)^3
  g2=cmul(cmul(cmul(g2,g2),g2),q);
  g2=cmul(g2,h2);
  //printf("g=256*(a^2-3)^3: %d %d\n",g2.re,g2.im);
  if(g2.re%p==g.re%p && g2.im%p==g.im%p){// && h2.re%p==h.re%p && h2.im%p==h.re%p){
  // if(jj==jj2 && i!=l && k!=n){
  //  if(g.re==g2.re && g.im==g2.im && h2.re%p==h.re%p && h2.im%p==h.im%p && i!=l && k!=n){
    printf("%d %d %d %d\n",g2.re,g2.im,h2.re,h2.im);
    //printf("%d %d %d %d\n",a1.re,a1.im,a2.re,a2.im);
    count++;
    //exit(1);
      }
}


  /*
  //f=a^2-4
  f=csub(r,f);
  printf("f=a^2-4: %d %d\n",f.re,f.im);

  //256(a^2-3)^3/(a^2-4)
  g=cdiv(g,f);
  
  printf("256(a^2-3)^3/(a^2-4): %d %d\n",g.re%p,g.im%p);
  h=cmul(g,v);
  printf("%d %d\n",h.re,h.im);
  exit(1);
  
  a2.re=162;
  a2.im=172;
  j=j_inv(a1);

  printf("%d %d\n",j.re%p,j.im%p);
  exit(1);
  j=j_inv(a2);

  printf("%d %d\n",j.re,j.im);

  return 0;
}
  */
