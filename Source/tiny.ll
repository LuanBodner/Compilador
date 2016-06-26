; ModuleID = 'tiny.bc'

@n = common global i32, align 4

define void @fatorial(i32 %f) {
entry_fatorial:
  %f.addr = alloca i32, align 4
  store i32 %f, i32* %f.addr
  %ret = alloca i32, align 4
  store i32 10, i32* %ret
  store i32 10, i32* %f.addr
}

define void @principal() {
entry_principal:
}
