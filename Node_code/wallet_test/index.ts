import { ethers } from "ethers";

const provider = new ethers.providers.JsonRpcProvider(
    "https://rpc.etdchain.net"
);

(async () => {
    console.log("Current block number", await provider.getBlockNumber());

    console.log("Latest block", await provider.getBlock("latest"));

    console.log(
        "Total number of transactions by wallet address",
        await provider.getTransactionCount("0x3b332A713c916DdAE24ad52BE96c199d0f7c27BA")
    );

    const balance = await provider.getBalance("0x3b332A713c916DdAE24ad52BE96c199d0f7c27BA");
    console.log("Balance in wei", balance);

    const balanceInEther = ethers.utils.formatEther(balance);
    console.log("Balance in ether", balanceInEther);

    const gasPrice = await provider.getGasPrice();
    console.log("Gas price in wei", gasPrice);
})()

