import { ipcMain } from 'electron'
import { IpcMainEvent } from 'electron/main';
import { exec } from 'child_process';

class ipcEvents {
    public static init() {
        ipcMain.on('test-event', this.onTestEvent);
    }

    public static async onTestEvent(event: IpcMainEvent, ...arg: any[]) {
        const thread = await execute("node --version");
        event.reply('test-event-reply', thread);



        // const thread = await spawnSync('npm', ["-v"], { shell: true, encoding: 'utf8', maxBuffer: 1024 * 500 });
    }
}

function execute(command) {
    return new Promise((resolve, reject) => {
        exec(command, (error, stdout, stderr) => {
            if (error) {
                reject();
        
                return;
              }
        
            if (stderr) {
                reject(stderr);
                return;
            }
        
            resolve(stdout);
            });
    });
}

export default ipcEvents
