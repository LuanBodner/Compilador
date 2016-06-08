; ModuleID = 'tiny.bc'

@global1 = external global i32
@global2 = external global i32

define i32 @teste(float) {
entry_teste:
  %a = alloca i32
  %b = alloca i32
  %c = alloca i32
  %j = alloca i32
  %k = alloca i32
  %l = alloca i32
  %aux = alloca float
}

define void @foo(i32) {
entry_foo:
  %abc = alloca float
  %a = alloca float
  %b = alloca i32
}

define void @principal() {
entry_principal:
}
