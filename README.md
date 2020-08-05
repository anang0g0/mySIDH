# mySIDH

202008004

安定版を保管するディレクトリを新たに追加しました。
カレントディレクトリは開発版です。
バグを指摘されたので直している途中です。

同じｊ不変量を持つ楕円曲線を総探索するプログラムに変更しました。(mini.c)

20200803

小さい例（64ビット）複素数型の計算で、ガウス整数の楕円曲線のｊ-不変量を計算できるようになりました。(mini.c)

大きな例は、mini.cppで扱えます。

20200801

よく読んでみれば、仕様書はなぜこうなるのかではなく、こうしろとしか書いてないので何も悩む必要がないことがわかった。
ただ複素数としてガウス整数を使っているので、複素数型を定義してやらないといけないけど、そういう実装上の問題だけで計算方法がわからないということはまずない。
必要な関数は全部揃っているし、初期値もきちんと書いてある。
なので、このまま実装を続けられそうだ。

20200731

いろいろ調べてわけが解らなくなったけど、ペアリングの応用は今に始まったことじゃないから、たった5本の論文に目を通しただけで理解できるものではなかったのだ。
一時は面倒で止めたくなったけど、そんな訳でまた始めてる。
解らないことを1つずつ解決していくのが研究なのだ。
なぜ虚数が出てくるのかも論文を調べていくうちに私が最初に思いついた虚二次体の整数論と関係しているのではないかという予感があった。
そして実際、虚二次体上の話もされていた。
それから超楕円曲線にも既に拡張されていた。
もっとたくさん論文を読めば解る気がしてきた。
なぜわからないのかと思ってパニックになりそうだったけど、解る気がしてきた。
虚数乗法とも関係があるみたいなので、そのへんは論文で確かめるつもりだ。

ON ELLIPTIC CURVES OF PRIME POWER CONDUCTOR OVER　IMAGINARY QUADRATIC FIELDS WITH CLASS NUMBER ONE

これなんかまさにぴったりだ。
類数1の楕円曲線だけをCM法で構成するプログラムを昔作って持っているので、いま活躍することになるかも知れない。

TOWARDS QUANTUM-RESISTANT CRYPTOSYSTEMS FROM SUPERSINGULAR ELLIPTIC CURVE ISOGENIES

これには虚二次体がでてくる。

https://github.com/defeo/ss-isogeny-software

調べていくうちに著者の書いたソースコードまで手に入ってオトクな気分。
実装するのに手がかりになりそう。
単なる論文の具体例だけでなく、実際に動かしてみることができる。
早とちりかも知れないけど、何だか楽しみ。

20200730

SIDH開発用のリポジトリを新規に作り、eccからリポジトリを分けました。

巨大整数計算ライブラリを以下のリポジトリを利用して使っています。
mathに数学関数を追加。

とりあえずSIDHのパラメータを設定するところまでは出来ています。
非力な環境でVPNルーターを作っている会社もありそうなので、そのへんのニッチを狙っていますｗ。

非力な環境では、mathライブラリも何もない状態だと思うので、最終的には基本的な数学関数から全部作って（あるいは移植して）全部自前でなんとかできるようにする必要が有りますが、
そのへんはアルゴリズム辞典かなんかで引用して済ませてください。

makeなんか動かないという環境では、Makefile の中身を見て手動で動かしてくださいｗ。

基礎となる論文を読んでいるので、計算の概要が分かり次第実装を始めようと思います。
参考にした論文はpaperの中に入っているので読んでください。

20200728

bigint.cの使い始めということもあり、まずは楕円曲線のパラメータを設定するプログラムを書いてみました。

sidh.c

sidh.cpp

です。

SIDHの仕様書。
1ページめから怒涛のアルゴリズム。
細かい計算とか考えると最終的に100くらいの関数を書くことになるのだろうか。
ネットで京大理学部卒の作家さんと、東大卒のエンジニアさんと話す機会があるのですが、暗号については数学者は興味がないしエンジニアには理解するのが難しい分野のようです。
東大出たんなら出来なくはないと思うのですが、必要性がないから書かないだけでしょうね。

20200727

http://cacr.uwaterloo.ca/techreports/2014/cacr2014-20.pdf

こんなに難しいのに、全然役に立たないなんて馬鹿にしてたら凄い活躍しててびっくり。
実はペアリングもわからないし、巨大整数も嫌いなんだけど、それじゃまるで逃げてるみたいだから癪に障る。

https://github.com/dconnolly/msr-sidh

いずれにしてもこういうコードが書けないと暗号技術者にはなれません。
更に定義体がECDLPの時のように素直じゃない。
二次の拡大体であるにもかかわらず、虚数が出てくることから、これが虚二次体上の整数論と関係があることに気付かないと意味不明なままです。
後、j-不変量なんてものも出てくるので要注意です。

https://sike.org/files/SIDH-spec.pdf (今回挑戦している仕様書)

こういう面倒なことはできるならやりたくない。
符号なら小さな数をたくさん集めるだけで安全な暗号になる。
何しろ符号は多項式と線形代数だけで作れるという分かりやすさがあるから、楕円曲線みたいな数学からの物体Xにならないんですよね。
それにどうせやるならみんなと同じことをやるんじゃなくて、やってないことをやる方が意味がある気がします。

符号も安全だけど、実は不器用なんだよね。
一つの暗号系でいろんなことが出来るペアリングとは対照的に、いまだに研究途中。
でもそれは多変数多項式系も同じようなもので、いまだに画期的で確実視されるような暗号はできていない。
そもそも多変数多項式でどうやって鍵共有できるのかという問題もある。
つまりペアリングベースの暗号が一番次世代に近い位置にあるわけ。

二日目にして早くもやる気をなくしている私。
もう符号があるから好きなときだけでいいやって感じ。
移植しても楕円なんでもうオワコンだし、やるんだったらSIDHだよねって感じで。
午前中で面倒になったｗ。

移植しようとするから悪いのだ。
どうせ全然違う方式だし計算式も変わっているのだから、1から作ればいいのだ。
やっぱり秘密鍵交換は必要だしね。

SIDHはかなりややこしい計算をしていて、関数だけでも50前後の数を書かないといけない。
しかも曲線のパラメーターが0と6の場合が有って、最新の情報だと６だけど、現存する実装では０になってたりする。
これはまだ、ドラフトの途中であることからこれからどんなふうに変わっていくかは確実じゃないからだ。
他の実装を見ても全部GMPを使っていて、やはり組み込みには使えない。
そして読んでもクソ長くて、でかいプログラム。
見るのもうんざりするけど書くのもうんざりするだろうなとｗ。
そして結論としては、やはり自分で納得の行くものを作る必要があるということ。
これは誰かのためになることでもあるだろうと、勝手に期待してしまうｗ。
ちょっと調査するから３日くらいしたら書き始めると思う。

20200725

弐号機再起動！楕円曲線の見事な復活というべきでしょうかｗ。

なんだかSIDHがものすごい勢いで実用化されていて、鍵交換どうしようかなーと迷っていたこともあって、秘密鍵暗号の設計がどうでも良くなりそうな感じです。

何だかいくらでも出てきそうな感じですが、楕円曲線が復活するとは思いませんでした。
中国の研究だと思ってたら、フランスの研究ですね。
この勢いで行くと、超楕円曲線も復活するかも知れないですね。
ちなみに超楕円曲線が超特異かどうかを知る方法は、つい最近までなかったらしい。

他の誰かが作った普通のCで書かれた巨大整数用プログラムを見つけたので、今後Pure C language で書き換えようと思ってます。
それで慣れてきたらいよいSIDHですかね。

今の所、NTL使って巨大整数を扱っているわけですが、まあ邪道ですねｗ。
組み込み環境みたいに言語が選べない人でちょっと面倒な人には、ちょうどいいプログラムがネットに落ちていたので、それを流用することに。
NTLも古いのしか使えないし。

確かに、SIDHだったらみんなが作っているようなので探せば実装はいくらでもある。
それがなかったからニーダーライター暗号を作れるように、自分用に作ったわけだけど。
SIDHなら鍵交換も、電子署名も、暗号化もできるし既存の方法よりはいろんなメリットがある。
でも、そこで私がまた自分のやり方で作る意味があるのか？という感じもする。
今更誰も使わないよね、っていう。
とりあえず知っておけば何かいいことがあるかもしれないという気がするだけ。
どうして急にやる気が出てきたかというと、楕円曲線周りは理論が難しいし、同種写像なんてものは聞いたことがないし、今から理解できる自信がなかったからだ。
でも、仕様書を見ると計算方法もパラメータも全部決まっているし、やっていることは楕円曲線とあまり変わりがない。
という訳で急に注目するようになったという感じだ。
このまま、古い楕円曲線を眠らせておくのはもったいないｗ。

すぐ欲しい人にはマイクロソフトが作ったSIDHがあるので、それを使うでしょうけど。












Discontinued in favour of https://github.com/983/Num

# bigint

C usage example:
```c
#include "bigint.h"

#include <stdio.h>

int main(){
    char buf[65536];

    /* neat trick to avoid having to write &a, &b, &c everywhere */
    bigint a[1], b[1], c[1];

    /* bigints have to be initialized (same as memset'ed to zero) */
    bigint_init(a);
    bigint_init(b);
    bigint_init(c);

    /* create bigint from string */
    bigint_from_str(a, "123456789");
    bigint_from_str(b, "987654321");

    /* c = a * b */
    /* first parameter is destination parameter */
    bigint_mul(c, a, b);

    /* write and print */
    puts(bigint_write(buf, sizeof(buf), c));

    /* bigints have to be free'd */
    bigint_free(a);
    bigint_free(b);
    bigint_free(c);

    return 0;
}
```

C++ usage example:
```cpp
#include "bigint.hpp"

#include <assert.h>
#include <iostream>

uint32_t xorshift32() {
    static uint32_t x = 314159265;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

// do not use this as a cryptographically secure random number generator
void not_secure_random(uint8_t *dst, int n){
    for (int i = 0; i < n; i++) dst[i] = xorshift32();
}

int main(){
    // BigInts can be created from strings or from integers
    BigInt a = "-1137531041259095389425522063651335971086542522289";
    BigInt b = "-9214001518046086468566115579527473139501";

    // Available operators:
    // +, -, *, /, %, <<, >>
    // +=, -=, *=, /=, %=, <<=, >>=, ++, --
    // ==, !=, <=, >=, <, >
    BigInt c = a / b;
    BigInt d = b * c;
    assert(c == 123456789);
    assert(a == d);

    // write to any output stream
    c.write(std::cout) << std::endl;
    d.write(std::cout) << std::endl;

    // find the biggest probable prime less than 10^42
    BigInt p = BigInt(10).pow(42) - 1;

    for (int i = 0; i < 100; i++){
        if (p.is_probable_prime(10, not_secure_random)){
            p.write(std::cout << "Big prime: ") << std::endl;
            break;
        }
        --p;
    }

    return 0;
}
```

Implementation notes:
* BigInts consist of an array of bigint_words which are unsigned ints as defined in bigint.h
* Try adjusting bigint_word in bigint.h for maximum performance
* If there is a highest word, it should always be non-zero, as assured by bigint_raw_truncate
* Multiplication uses [the Karatsuba algorithm](https://en.wikipedia.org/wiki/Karatsuba_algorithm) for large integers
* The C++ interface is easier to use, but the C interface is better at avoiding reallocations
* If you have to calculate both division and modulo, use div_mod
* The bigint_raw_* methods expect the dst parameter to be sufficiently big, so be careful with those!

Things to do on rainy days:
* Improve performance for reading and writing bigints with 2^n bases
* Extract many digits per division for bigint_write_base
