import { expect } from "chai";
import { ethers } from "hardhat";

async function deploy() {
    const [minter, redeemer, _] = await ethers.getSigners()

    let factory = await ethers.getContractFactory("Trading", minter)
    const contract = await factory.deploy(minter.address)

    const redeemerFactory = factory.connect(redeemer)
    const redeemerContract = redeemerFactory.attach(await contract.getAddress())

    return {
        minter,
        redeemer,
        contract,
        redeemerContract,
    }
}

describe("Trading", function () {
    it("Should deploy", async function () {
        const signers = await ethers.getSigners();
        const minter = signers[0].address;

        const Trading = await ethers.getContractFactory("Trading");
        const trading = await Trading.deploy(minter);
        await trading.waitForDeployment();
    });

    it("Should redeem an NFT from a signed voucher", async function () {
        const { contract, redeemerContract, redeemer, minter } = await deploy()

        const lazyMinter = new LazyMinter({ contract, signer: minter })
        const voucher = await lazyMinter.createVoucher(1, "ipfs://bafybeigdyrzt5sfp7udm7hu76uh7y26nf3efuylqabf3oclgtqy55fbzdi")

        await expect(redeemerContract.redeem(redeemer.address, voucher))
            .to.emit(contract, 'Transfer')  // transfer from null address to minter
            .withArgs('0x0000000000000000000000000000000000000000', minter.address, voucher.tokenId)
            .and.to.emit(contract, 'Transfer') // transfer from minter to redeemer
            .withArgs(minter.address, redeemer.address, voucher.tokenId);
    });
});