class Patient {
    constructor(public id: string, public name: string, public age: number, public gender: string,
        public phoneNumber: string, public department: number, 
        public doctorid: number, public treatmentTime: string,
        public bTreatmentTime: string = "", public endTime: string = "", public bEndTime: string = "", 
        public bTag: boolean = false, public bDoctorid: boolean = false) { }
}
module.exports = Patient;
export {}