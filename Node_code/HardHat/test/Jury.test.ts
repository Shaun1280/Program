import { time } from "@nomicfoundation/hardhat-network-helpers";
import { expect } from "chai";
import { ethers } from "hardhat";

describe("Jury", function () {
    it("should be able to assess", async function () {
        const [owner, voter1, voter2, candidate1, candidate2] =
            await ethers.getSigners();
        const Jury = await ethers.getContractFactory("Jury");
        const jury = await Jury.deploy(3000);
        await jury.waitForDeployment();

        // register candidates
        await jury.connect(candidate1).registerArt(0);
        await jury.connect(candidate2).registerArt(1);

        await jury.connect(voter1).assess(0, 100);
        await jury.connect(voter1).assess(1, 30);
        await jury.connect(voter2).assess(0, 50);
        await jury.connect(voter2).assess(1, 100);

        const results = await jury.getResults();
        // console.log(results);
        expect(results).to.have.length(2);
        expect(results[0].assessment.length).to.equal(2);
        console.log(results[0]);
        expect(results[1].assessment.length).to.equal(2);
        console.log(results[1]);
    });

    it("Should not be able to register when voting is ended", async function () {
        const [owner, voter1, voter2, candidate1, candidate2] =
            await ethers.getSigners();
        const Jury = await ethers.getContractFactory("Jury");
        const jury = await Jury.deploy(3000);
        await jury.waitForDeployment();

        await time.increase(4000);

        await expect(
            jury.connect(voter1).registerArt(0)
        ).to.be.revertedWith("Voting is ended");
    });

    it("Should not be able to vote when voting is ended", async function () {
        const [owner, voter1, voter2, candidate1, candidate2] =
            await ethers.getSigners();
        const Jury = await ethers.getContractFactory("Jury");
        const jury = await Jury.deploy(3000);
        await jury.waitForDeployment();

        await jury.connect(candidate1).registerArt(0);

        await time.increase(4000);

        await expect(jury.connect(voter1).assess(0, 100)).to.be.revertedWith(
            "Voting is ended"
        );
    });
});