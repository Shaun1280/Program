import { ethers } from "ethers";

// We need to use async/await syntax in typescript,
// so we create a top-level async function.
// ignore this syntax if you don't understand
(async () => {
    const provider = new ethers.providers.JsonRpcProvider(
        "https://rpc.debugchain.net"
    );

    // we will get wallet from private key
    const wallet = new ethers.Wallet(process.env.pk!, provider);

    // put your receiver here
    const receiver = "0xDF721c726467bE31fcD5940Ca6FfF1Dea7f251B3";

    // get total transaction count from sender as nonce
    const nonce = await provider.getTransactionCount(wallet.address);

    // sign transaction
    const signedTransaction = await wallet.signTransaction({
        to: receiver,
        value: ethers.utils.parseEther("0.01"),
        nonce: nonce,
        gasPrice: await provider.getGasPrice(),
        gasLimit: 21000,
        chainId: 8348
    });

    console.log("Signed transaction", signedTransaction);

    const txId = await provider.sendTransaction(signedTransaction);
    console.log("Transaction id", txId);
})();
