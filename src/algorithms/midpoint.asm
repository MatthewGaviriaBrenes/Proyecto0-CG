;Matthew Gaviria Brenes
section .text
    global midpoint_asm

midpoint_asm:
    ;save function registers
    push rbx
    push r12
    push r13
    push r14
    push r15

    ;Store arguments
    mov r12, rdi        ; r12 = x0
    mov r13, rsi        ; r13 = y0
    mov r14, rdx        ; r14 = x1
    mov r15, rcx        ; r15 = y1
    mov rbx, r8         ; rbx = plot

    ;reserve stack space for variables.
    sub rsp, 48

    ;dx = abs(x1 - x0) absolute x distance
    mov eax, r14d
    sub eax, r12d

    cmp eax, 0
    jge .dx_positive
    neg eax

.dx_positive:
    mov [rsp + 0], rax ;dx

    ;dy = abs(y1 - y0) absolute y distance
    mov eax, r15d
    sub eax, r13d

    cmp eax, 0
    jge .dy_positive
    neg eax

.dy_positive:
    mov [rsp + 8], rax ;dy

    ;sx = (x0 < x1) ? 1 : -1
    cmp r12d, r14d
    jl .sx_positive

    mov qword [rsp + 16], -1 ;sx 
    jmp .sx_done

.sx_positive:
    mov qword [rsp + 16], 1 ;sx

.sx_done:
    ;sy = (y0 < y1) ? 1 : -1
    cmp r13d, r15d
    jl .sy_positive

    mov qword [rsp + 24], -1 ;sy
    jmp .sy_done

.sy_positive:
    mov qword [rsp + 24], 1 ;sy

.sy_done:

    ;error = dx - dy
    mov rax, [rsp + 0]  ;dx
    sub rax, [rsp + 8]  ;dy
    mov [rsp + 32], rax ;rps + 32: error

;while. continue until reaching endpoint
.loop:

    ;plot(x0, y0)
    mov rdi, r12
    mov rsi, r13
    call rbx


    ;if (x0 == x1 && y0 == y1)
    ;    break;
    cmp r12d, r14d
    jne .continue_loop

    cmp r13d, r15d
    je .done

.continue_loop:
    ;error2 = 2 * error
    mov rax, [rsp + 32] ;rps + 32: error
    add rax, rax
    mov [rsp + 40], rax ;rps + 40: error2

    ;if (error2 > -dy)
    ;{
    ;    error -= dy;
    ;    x0 += sx;
    ;}
    mov rax, [rsp + 8]      ;rax = dy
    neg rax                 ;rax = -dy

    cmp [rsp + 40], rax     ;error2 > -dy ?
    jle .skip_x

    ;error -= dy
    mov rax, [rsp + 32] ;error
    sub rax, [rsp + 8]  ;dy
    mov [rsp + 32], rax ;error

    ;x0 += sx
    mov rax, [rsp + 16] ;sx
    add r12, rax

.skip_x:
    ;if (error2 < dx)
    ;{
    ;    error += dx;
    ;    y0 += sy;
    ;}
    mov rax, [rsp + 0]      ;rax = dx
    cmp [rsp + 40], rax     ;error2 < dx ?
    jge .skip_y

    ;error += dx
    mov rax, [rsp + 32]
    add rax, [rsp + 0]
    mov [rsp + 32], rax

    ;y0 += sy
    mov rax, [rsp + 24]
    add r13, rax

.skip_y:
    jmp .loop

.done:
    ;clear local variables

    add rsp, 48

    ;Restore registers
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx

    ret


section .note.GNU-stack noalloc noexec nowrite progbits