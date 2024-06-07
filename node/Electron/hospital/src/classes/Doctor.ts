const Queue = require("../classes/Queue.js")
const Patient = require("../classes/Patient.js")

type Patient = InstanceType<typeof Patient>;
type Queue = InstanceType<typeof Queue>;

const { Notification } = require('electron');
let notification;

class Doctor {
    private historyPatientList: Array<Patient>; // 历史病人信息
    private queueReturnPatient: Queue; // 复诊病人队列
    private id: number; // 医生编号
    private type: number; // 1-15 普通医生 16 B超室医生
    private nextPatient?: Patient; // 下一位就诊病人
    private currentPatient?: Patient; // 当前就诊病人
    private leavePatient?: Patient; // 离开的病人

    constructor(_id: number, _type: number) {
        this.historyPatientList = new Array<Patient>();
        this.queueReturnPatient = new Queue();
        this.type = _type;
        this.id = _id;
    }

    // 能否分配下一个新病人 会将复诊病人分配
    canAllocateNextNewPatient(): boolean {
        if (this.isBusy() || this.nextPatient != null) return false;
        let returnPatient = this.queueReturnPatient.pop();
        if (returnPatient === undefined) {
            return true;
        } else {
            // 接收复诊病人 未正式诊断
            this.nextPatient = returnPatient;
            return false;
        }
    }

    // 分配下一个新病人
    allocateNextNewPatient(patient: Patient): void {
        this.nextPatient = patient;
        if (this.type != 16) this.nextPatient.doctorid = this.id;
        else this.nextPatient.bDoctorid = this.id;
    }

    // 开始诊断下一个病人 并通过 notification 发送通知
    treatNextPatient(): void { 
        this.currentPatient = this.nextPatient;
        if (this.nextPatient == null) return;
        this.nextPatient = null;

        if (this.currentPatient.treatmentTime === "") { // 普通科室新病人
            this.currentPatient.treatmentTime = this.GetTreatmentTime();
            this.historyPatientList.push(this.currentPatient); // 病人加入历史就诊表
            this.sendNotification();
        } else if (this.currentPatient.bTreatmentTime === "") { // B 超室新病人
            this.currentPatient.bTreatmentTime = this.GetTreatmentTime();
            this.historyPatientList.push(this.currentPatient); // 病人加入历史就诊表
            this.sendNotification();
        } else { // 复诊病人
            // 不需要额外操作 仅在结束时设置就诊结束时间
        }
    }

    // 发送通知
    sendNotification(): void {
        if (notification != undefined) notification.close();
        notification = new Notification({
                title: '通知 @',
                body: this.type == 16 ? `@ 请 ${this.currentPatient.id} 号 ` + this.currentPatient.name + ` 到 B 超室 doctor-${this.id} 处进行 B 超检查` : `@ 请 ${this.currentPatient.id} 号 ` + this.currentPatient.name + ` 到 ${this.type} 号科室 doctor-${this.id} 处就诊`,
                silent: false,
                timeoutType: 'default'
            });
        notification.show();
    }

    // 接收复诊病人 加入到队列
    enqueReturnPatient(patient: Patient): void { 
        this.queueReturnPatient.push(patient);
    }

    // 完成就诊
    done(): void { 
        this.leavePatient = this.currentPatient;

        // 未开 B 超 或者已做过 B 超，诊断完全结束
        if (this.leavePatient.bTag == false) this.leavePatient.endTime = this.GetTreatmentTime();
        else if (this.type != 16) {
            // 做过 B 超检查的复诊病人
            if (this.leavePatient.bTreatmentTime != "") this.leavePatient.endTime = this.GetTreatmentTime();
        } else { // B 超室检查结束
            this.leavePatient.bEndTime = this.GetTreatmentTime();
        }

        this.currentPatient = null;
    }
    // 设置 B 超标记
    setUltraSoundTag(): void { this.currentPatient.bTag = true; }
    // 判断医生是否忙碌
    isBusy(): boolean { return this.currentPatient != null; }

    // Geters
    // 返回医生状态
    getStatus(): number {
        if (this.currentPatient != null) return 2; // 忙碌
        if (this.nextPatient != null) return 1; // 病人等候中
        return 0; // 空闲
    }
    // 返回历史就诊信息表
    getHistoryPatientList(): Array<Patient> {
        return this.historyPatientList;
    }
    // 返回离开的病人
    getLeavePatient(): Patient { return this.leavePatient; }
    // 返回当前病人
    getCurrentPatient(): Patient { return this.currentPatient; }
    // 返回下一位病人
    getNextPatient(): Patient { return this.nextPatient; }
    // 获取当前时间
    private GetTreatmentTime():string {
        let now = new Date();
        let year = now.getFullYear();
        let month = now.getMonth() + 1;
        let date = now.getDate();
        let hour = now.getHours();
        let minu = now.getMinutes();
        let sec = now.getSeconds();
        let _time = year + "-" + month + "-" + date + " " + hour + ":" + minu + ":" + sec;
        return _time;
    }
};
module.exports = Doctor;
export {}