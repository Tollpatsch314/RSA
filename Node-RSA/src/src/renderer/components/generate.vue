<template>
    <div class="Page">
        <h1>Erzeugung</h1>

        <div class="Box">
            <h1 style="padding-bottom: 0.1rem;">Public Key</h1>
            <textarea class="one" style="resize: none;" v-model="publicKey" @input="changePublic" />
            <br>
            <h1 style="padding-bottom: 0.1rem;">Private Key</h1>
            <textarea class="two" style="resize: none;" v-model="privateKey" @input="changePrivat" />
        </div>

        <button @click="generateKeys">Generate</button>
    </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue';

import NodeRSA from '@renderer/plugins/nodeRSA';
const rsa = NodeRSA.getInstance();

export default defineComponent({
    name: 'generate',
    data() {
        return  {
            publicKey: "",
            privatKey: "",
        }
    },
    methods: {
        changePublic(e: Event) {
            if(rsa.getRSA() == null) {
                rsa.createRSA();
            }
            
            if(e.target["value"] != "") {
                // Check if the public key is valid
                try {
                    rsa.getRSA().importKey(this.publicKey, 'pkcs8-public-pem');
                    this.publicKey = rsa.getRSA().exportKey('pkcs8-public-pem');
                } catch(e) {
                    this.publicKey = "";
                    return;
                }
            } else {
                this.publicKey = "";
                rsa.removeRSA();
            }
        },

        changePrivat(e: Event) {
            if(rsa.getRSA() == null) {
                rsa.createRSA();
            }

            if(e.target["value"] != "") {
                // Check if the private key is valid
                try {
                    rsa.getRSA().importKey(this.privateKey, 'pkcs8-private-pem');
                    this.privateKey = rsa.getRSA().exportKey('pkcs8-private-pem');
                } catch(e) {
                    this.privateKey = "";
                    return;
                }
            } else {
                this.privateKey = "";
                rsa.removeRSA();
            }
        },

        generateKeys() {
            if(rsa.getRSA() == null) {
                rsa.createRSA();
            }

            rsa.getRSA().generateKeyPair(1024, 65537);

            const publicKey = rsa.getRSA().exportKey('pkcs8-public-pem');
            const privateKey = rsa.getRSA().exportKey('pkcs8-private-pem');

            this.publicKey = publicKey;
            this.privateKey = privateKey;

        }
    },
    mounted() {
        
    }
})
</script>

<style lang="less" scoped>
div.Page {
    display: flex;
    flex-wrap: nowrap;
    align-content: center;
    justify-content: flex-start;
    flex-direction: column;
    align-items: center;

    h1 {
        font-size: 2vw;
        margin: 0;
        padding: 1vw 0 0 0;
        pointer-events: none;
        user-select: none;
    }

    div.Box {
        padding: 0;
        margin: 1vw 0vw;
        width: 30vw;
        height: 46vw;
        border: 1px solid grey;

        display: flex;
        flex-direction: column;
        flex-wrap: nowrap;
        align-content: center;
        justify-content: center;
        align-items: center;

        textarea.one {
            width: 26vw;
            height: 12vw;
        }

        textarea.two {
            width: 26vw;
            height: 20vw;
        }
    }

    button {
        margin: 0 0;
        padding: 0 0;
        
        font-size: 1vw;
        width: 20vw;
        height: 2.5vw;
        border-radius: 0.5vw;
        border: none;

        color: white;
        background-color: #c93b3b;

        &:hover {
            background-color: #bb4242;
        }
    }
}
</style>