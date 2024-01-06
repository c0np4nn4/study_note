program mission_2.aleo;

record token:
    owner as address.private;
    amount as u64.private;


mapping balances:
	key as address.public;
	value as u64.public;

function mint_private:
    input r0 as address.private;
    input r1 as u64.private;
    cast r0 r1 into r2 as token.record;
    output r2 as token.record;


function mint_public:
    input r0 as address.public;
    input r1 as u64.public;
    cast r0 r1 into r2 as token.record;
    async mint_public r0 r1 into r3;
    output r2 as token.record;
    output r3 as mission_2.aleo/mint_public.future;

finalize mint_public:
    input r0 as address.public;
    input r1 as u64.public;
    get.or_use balances[r0] 0u64 into r2;
    add r2 r1 into r3;
    set r3 into balances[r0];
