// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.9;

struct NFTVoucher {
    //The id of the token to be redeemed.
    // Must be unique
    // if another token with this ID already exists, the redeem function will revert.
    uint256 tokenId;
    // The minimum price (in wei) that the NFT creator is willing to accept
    // for the initial sale of this NFT.
    uint256 minPrice;
    // The metadata URI to associate with this token.
    string uri;
    // the EIP-712 signature of all other fields in the NFTVoucher struct.
    // For a voucher to be valid
    // it must be signed by an account with the MINTER_ROLE.
    bytes signature;
}

struct Candidate {
    address owner;
    uint256 tokenId;
}

struct Assessment {
    address judger;
    uint256 price;
}

struct Result {
    uint256 tokenId;
    Assessment[] assessment;
}
