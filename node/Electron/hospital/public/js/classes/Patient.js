"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
class Patient {
    constructor(id, name, age, gender, phoneNumber, department, doctorid, treatmentTime, bTreatmentTime = "", endTime = "", bEndTime = "", bTag = false, bDoctorid = false) {
        this.id = id;
        this.name = name;
        this.age = age;
        this.gender = gender;
        this.phoneNumber = phoneNumber;
        this.department = department;
        this.doctorid = doctorid;
        this.treatmentTime = treatmentTime;
        this.bTreatmentTime = bTreatmentTime;
        this.endTime = endTime;
        this.bEndTime = bEndTime;
        this.bTag = bTag;
        this.bDoctorid = bDoctorid;
    }
}
module.exports = Patient;
