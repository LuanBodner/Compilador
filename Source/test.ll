; ModuleID = 'test.bc'

define i32 @mul_add(i32 %x, i32 %y, i32 %z) {
entry:
  %Name = alloca i32
  store i32 30, i32* %Name
  ret i32 30
}
