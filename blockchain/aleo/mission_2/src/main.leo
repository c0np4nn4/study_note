program mission_2.aleo {
    mapping balances: address => u64;

    record token {
        owner: address,
        amount: u64,
    }

    transition mint_private(
        receiver: address,
        amount: u64,
    ) -> token {
				let new_token: token = token {
					owner: receiver,
					amount
				};

        return new_token;
    }

    transition mint_public(
        public receiver: address,
        public amount: u64,
    ) -> token {
				let new_token: token = token {
					owner: receiver,
					amount
				};

        return new_token then finalize(receiver, amount);
    }

    finalize mint_public(
        public receiver: address,
        public amount: u64,
    ) {
        let current_amount: u64 = Mapping::get_or_use(balances, receiver, 0u64);
				// let new_amount: u64 = add_u64(current_amount + amount);        
				// Mapping::set(balances, receiver, new_amount);
				Mapping::set(balances, receiver, current_amount + amount);
   }
		
		/*
    function add_u64(a: u64, b: u64) -> u64 {
        return a + b;
    }
		*/
}
