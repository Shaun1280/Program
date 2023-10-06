import { expect } from "chai";
import { ethers } from "hardhat";
import { LazyMinter } from '../lib/LazyMinter';

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
        const voucher = await lazyMinter.createVoucher(
            1,
            "ipfs://Qmb9vsjexQs4uVMN8MSv7jvoNogixh2kuAc66KbQHDgsKQ"
        )

        await expect(redeemerContract.redeem(redeemer.address, voucher))
            .to.emit(contract, 'Transfer')  // transfer from null address to minter
            .withArgs('0x0000000000000000000000000000000000000000', minter.address, voucher.tokenId)
            .and.to.emit(contract, 'Transfer') // transfer from minter to redeemer
            .withArgs(minter.address, redeemer.address, voucher.tokenId);
    });

    it("Should fail to redeem an NFT that's already been claimed", async function () {
        const { contract, redeemerContract, redeemer, minter } = await deploy()

        const lazyMinter = new LazyMinter({ contract, signer: minter })
        const voucher = await lazyMinter.createVoucher(
            1,
            "ipfs://Qmb9vsjexQs4uVMN8MSv7jvoNogixh2kuAc66KbQHDgsKQ"
        )

        await expect(redeemerContract.redeem(redeemer.address, voucher))
            .to.emit(contract, 'Transfer')  // transfer from null address to minter
            .withArgs('0x0000000000000000000000000000000000000000', minter.address, voucher.tokenId)
            .and.to.emit(contract, 'Transfer') // transfer from minter to redeemer
            .withArgs(minter.address, redeemer.address, voucher.tokenId);

        await expect(redeemerContract.redeem(redeemer.address, voucher))
            .to.be.revertedWith('ERC721: token already minted')
    });

    it("Should fail to redeem an NFT voucher that's signed by an unauthorized account", async function () {
        const { contract, redeemerContract, redeemer, minter } = await deploy()

        const signers = await ethers.getSigners()
        const rando = signers[signers.length - 1];

        const lazyMinter = new LazyMinter({ contract, signer: rando })
        const voucher = await lazyMinter.createVoucher(
            1,
            "ipfs://Qmb9vsjexQs4uVMN8MSv7jvoNogixh2kuAc66KbQHDgsKQ"
        )

        await expect(redeemerContract.redeem(redeemer.address, voucher))
            .to.be.revertedWith('Signature invalid or unauthorized')
    });

    it("Should fail to redeem an NFT voucher that's been modified", async function () {
        const { contract, redeemerContract, redeemer, minter } = await deploy()

        const signers = await ethers.getSigners()
        const rando = signers[signers.length - 1];

        const lazyMinter = new LazyMinter({ contract, signer: rando })
        const voucher = await lazyMinter.createVoucher(
            1,
            "ipfs://Qmb9vsjexQs4uVMN8MSv7jvoNogixh2kuAc66KbQHDgsKQ"
        )

        voucher.tokenId = 2
        await expect(redeemerContract.redeem(redeemer.address, voucher))
            .to.be.revertedWith('Signature invalid or unauthorized')
    });

    it("Should fail to redeem if payment is < minPrice", async function () {
        const { contract, redeemerContract, redeemer, minter } = await deploy()

        const lazyMinter = new LazyMinter({ contract, signer: minter })
        const minPrice = ethers.WeiPerEther // charge 1 Eth
        const voucher = await lazyMinter.createVoucher(
            1,
            "ipfs://Qmb9vsjexQs4uVMN8MSv7jvoNogixh2kuAc66KbQHDgsKQ",
            BigInt.asUintN(256, minPrice)
        )

        const payment = minPrice - BigInt("1000");
        await expect(redeemerContract.redeem(redeemer.address, voucher, { value: payment }))
            .to.be.revertedWith('Insufficient funds to redeem')
    })

    it("Should make payments available to minter for withdrawal", async function () {
        const { contract, redeemerContract, redeemer, minter } = await deploy()

        const lazyMinter = new LazyMinter({ contract, signer: minter })
        const minPrice = ethers.WeiPerEther // charge 1 Eth
        const voucher = await lazyMinter.createVoucher(
            1,
            "ipfs://Qmb9vsjexQs4uVMN8MSv7jvoNogixh2kuAc66KbQHDgsKQ",
            BigInt.asUintN(256, minPrice)
        )

        // the payment should be sent from the redeemer's account to the contract address
        await expect(await redeemerContract.redeem(redeemer.address, voucher, { value: minPrice }))
            .to.changeEtherBalances([redeemer, contract], [-BigInt.asUintN(256, minPrice), BigInt.asUintN(256, minPrice)])

        // minter should have funds available to withdraw
        expect(await contract.availableToWithdraw()).to.equal(minPrice)

        // withdrawal should increase minter's balance
        await expect(await contract.withdraw())
            .to.changeEtherBalance(minter, minPrice)

        // minter should now have zero available
        expect(await contract.availableToWithdraw()).to.equal(0)
    })
});