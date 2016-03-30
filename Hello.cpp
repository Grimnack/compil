//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
using namespace llvm;

#define DEBUG_TYPE "hello"

// Commande utile :
// lclang -S -emit-llvm -Xclang -load -Xclang ../../../Release+Asserts/lib/LLVMHello.so hello.c -o /tmp/awesome.ll


// Affiche I m running on a block a chaque fois qu'on rentre dans un bloc

namespace {
class MyPass : public BasicBlockPass {
public:
  static char ID;

  MyPass() : BasicBlockPass(ID) {}

  bool runOnBasicBlock (BasicBlock &BB) override {
    errs() << "I m running on a block...\n";
    for (typename BasicBlock::iterator I = BB.getFirstInsertionPt(), end = BB.end(); I != end; I++) {
      Instruction &Inst = *I;
      for(size_t i = 0; i < Inst.getNumOperands();++i) {
        if(Constant *C = isValidCandidateOperand(Inst.getOperand(i))) {
          errs() << "I've found one sir!\n" ;
        }
      }
    }
    return false;
  }

private:
  void registerInteger(Value &V) {
    if (V.getType()->isIntegerTy()) {
      IntegerVect.push_back(&V);
      errs() << "Registering an integer!" << V << "\n";
    }
  }

  Constant *isValidCandidateOperand(Value *V) {
    Constant *C;
    if (!(C = dyn_cast<Constant>(V))) return nullptr;
    if (!C->isNullValue()) return nullptr;
    if (!C->getType()->isIntegerTy()) return nullptr;
  return C;
  }
};
}


char MyPass::ID = 0;
static RegisterPass<MyPass> X("MyPass", "Obfuscates zeroes",
                                     false, false);

// register pass for clang use
static void registerMyPassPass(const PassManagerBuilder &,
                               PassManagerBase &PM) {
  PM.add(new MyPass());
}
static RegisterStandardPasses
    RegisterMBAPass(PassManagerBuilder::EP_EarlyAsPossible,
                    registerMyPassPass);