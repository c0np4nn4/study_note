// The 'my_first_leo_program' program.
program my_first_leo_program.aleo {
    transition main(public a: u32, b: u32) -> u32 {
        let c: u32 = a + b;
        return c;
    }
}
