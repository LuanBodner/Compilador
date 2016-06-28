; ModuleID = 'tiny.bc'

define i32 @bar(i32 %c, i32 %d) {
entry_bar:
  %c.addr = alloca i32, align 4
  store i32 %c, i32* %c.addr
  %d.addr = alloca i32, align 4
  store i32 %d, i32* %d.addr
  store i32 -15, i32* %c.addr
  store i32 12, i32* %d.addr
  ret i32 10
}

define void @foo(i32 %a, double %b) {
entry_foo:
  %a.addr = alloca i32, align 4
  store i32 %a, i32* %a.addr
  %b.addr = alloca double, align 4
  store double %b, double* %b.addr
  store i32 10, i32* %a.addr
  store double 1.100000e+01, double* %b.addr
  %l = alloca i32, align 4
  store i32 8, i32* %l
  call void @foo(i32 11, double 1.200000e+01)
}

define void @principal() {
entry_principal:
  %a = alloca i32, align 4
  store i32 10, i32* %a
  call void @foo(i32 0, double 0.000000e+00)
}
