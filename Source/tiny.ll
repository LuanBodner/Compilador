; ModuleID = 'tiny.bc'

@global0 = common global i32, align 4
@global1 = common global float, align 4

define void @bar(i32 %c, i32 %d) {
entry_bar:
  %k = alloca i32, align 4
  %m = alloca float, align 4
}

define void @foo(i32 %a, float %b) {
entry_foo:
  %l = alloca float, align 4
}

define void @principal() {
entry_principal:
}
