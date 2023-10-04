import { ethers } from "hardhat";

async function main() {
  const Contract = await ethers.getContractFactory("MSBD5017Token");
  const contract = await Contract.deploy();

  await contract.waitForDeployment();
  console.log("Contract deployed to:", await contract.getAddress());
}

// We recommend this pattern to be able to use async/await everywhere
// and properly handle errors.
main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});