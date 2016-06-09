; ModuleID = 'tiny.bc'

define void @principal() {
entry_principal:
  %a = alloca i32
  %b = alloca i32
  %c = alloca i32
  
  %a1 = load i32, i32* %a
  %c2 = load i32, i32* %c
  %b3 = load i32, i32* %b
}
