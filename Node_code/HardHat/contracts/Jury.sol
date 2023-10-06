// SPDX-License-Identifier: GPL-3.0
pragma solidity ^0.8.9;

import "./Types.sol";

contract Jury {
    // art list
    uint256[] public art;
    mapping(uint256 => Assessment[]) public assessmentReceived;
    // voter list
    address[] public jury;
    mapping(address => mapping(uint256 => bool)) public juryStatus;
    // owner of the contract
    address public owner;
    // start time of the voting
    uint256 public startTime;
    // end time of the voting
    uint256 public endTime;

    constructor(uint256 _endTime) {
        owner = msg.sender;
        startTime = block.timestamp;
        endTime = block.timestamp + _endTime;
    }

    // is the voting ended?
    function isEnded() public view returns (bool) {
        return block.timestamp > endTime;
    }

    // reset the voting
    // function reset(uint256 _endTime) public {
    //     require(msg.sender == owner, "Only owner can reset the voting");
    //     for (uint256 i = 0; i < candidates.length; i++) {
    //         votesReceived[candidates[i].candidateAddress] = 0;
    //     }
    //     // reset the candidate array
    //     delete candidates;
    //     // reset the voter list
    //     for (uint256 i = 0; i < voters.length; i++) {
    //         voterStatus[voters[i]] = false;
    //     }
    //     delete voters;
    //     // reset the total votes
    //     totalVotes = 0;
    //     // reset the start time
    //     startTime = block.timestamp;
    //     endTime = startTime + _endTime;
    //     emit Reset();
    // }

    // register a candidate
    function registerArt(uint256 artId) public {
        require(!isEnded(), "Voting is ended");
        uint8 ok = 1;
        for (uint256 i = 0; i < art.length; i++) {
            if (art[i] == artId) {
                ok = 0;
                break;
            }
        }

        require(ok == 1, "This art has already been registered");

        art.push(artId);
        assessmentReceived[artId] = new Assessment[](0);
    }

    // vote for a candidate
    function assess(uint256 artId, uint256 price) public {
        require(!isEnded(), "Voting is ended");
        require(!juryStatus[msg.sender][artId], "Already voted");

        assessmentReceived[artId].push(Assessment(msg.sender, price));
        juryStatus[msg.sender][artId] = true;
        jury.push(msg.sender);
    }
}
