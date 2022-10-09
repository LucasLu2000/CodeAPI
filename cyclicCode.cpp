#include "cyclicCode.h"

CyclicCode::CyclicCode() : Code() {

}

CyclicCode::CyclicCode(int the_n, int the_k, int the_d, int the_q) : Code(the_n, the_k, the_d, the_q) {

}

void CyclicCode::setGenerator(const Row<int> the_gen) {
    generator = the_gen;
}

Row<int> CyclicCode::getGenerator(){
    return generator;
}

Row<int> CyclicCode::CyclicEncode(const Row<int> the_word, const Row<int> the_gen){
    return modMatrix(conv(the_word, generator),q);
}

Row<int> CyclicCode::CyclicDecode(const Row<int> the_receivedWord){

}
