<template>
    <div class="Page">
        <h1>Entschlüsseln</h1>

        <div class="Box">
            <h1 style="padding-bottom: 0.1rem;">Text</h1>
            <textarea class="one" style="resize: none;" v-model="text" />
            <br>
            <h1 style="padding-bottom: 0.1rem;">Entschlüsselter Text</h1>
            <textarea class="two" style="resize: none;" v-model="decryptText" />
        </div>

        <button @click="decrypt">Entschlüsseln</button>
    </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import NodeRSA from '@renderer/plugins/nodeRSA';
const rsa = NodeRSA.getInstance();

export default defineComponent({
    name: 'decrypt',
    data() {
        return {
            text: "",
            decryptText: "",
        }
    },
    methods: {
        decrypt() {
            if(this.text) {
                if(rsa.getRSA() == null) {
                    return;
                }

                this.decryptText = rsa.getRSA().decryptPublic(this.text, 'utf8');
            }
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
        height: 83vh;
        border: 0.1vw solid grey;

        display: flex;
        flex-direction: column;
        flex-wrap: nowrap;
        align-content: center;
        justify-content: center;
        align-items: center;

        textarea.one {
            width: 26vw;
            height: 18vh;
        }

        textarea.two {
            width: 26vw;
            height: 40vh;
        }
    }

    button {
        margin: 0 0;
        padding: 0 0;
        
        font-size: 1vw;
        width: 20vw;
        height: 5vh;
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