; ModuleID = 'tiny.bc'

@global0 = common global i32, align 4
@global1 = common global float, align 4

define void @bar(i32 %c, i32 %d) {
entry_bar:
  %c.addr = alloca i32, align 4
  store i32 %c, i32* %c.addr
  %d.addr = alloca i32, align 4
  store i32 %d, i32* %d.addr
  store i32 2, i32* %c.addr
  store i32 -2, i32* %d.addr
  %k = alloca i32, align 4
  store i32 100, i32* %k
  %m = alloca i32, align 4
  store i32 10, i32* %m
  store i32 10, i32* @global0
}

define void @foo(i32 %a, i32 %b) {
entry_foo:
  %a.addr = alloca i32, align 4
  store i32 %a, i32* %a.addr
  %b.addr = alloca i32, align 4
  store i32 %b, i32* %b.addr
  store i32 10, i32* %a.addr
  store i32 11, i32* %b.addr
  %l = alloca i32, align 4
  store i32 8, i32* %l
}

define void @principal() {
entry_principal:
  %a = alloca i32, align 4
  store i32 10, i32* %a
}
