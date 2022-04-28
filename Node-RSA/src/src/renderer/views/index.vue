<template>
  <div class="App">
      <div class="Site">
        <Generate />
      </div>
      <div class="Site">
        <Encrypt />
      </div>
      <div class="Site">
        <Decrypt />
      </div>
  </div>
</template>

<script lang="ts">
import { defineComponent } from 'vue';
import Generate from '@renderer/components/generate.vue';
import Decrypt from '@renderer/components/decrypt.vue';
import Encrypt from '@renderer/components/encrypt.vue';

const componentName = 'App';
export default defineComponent({
  name: componentName,

  components: {
    Generate,
    Decrypt,
    Encrypt
  }, 
})
</script>

<style lang="less" scoped>
  div.App {
    width: 100vw;
    height: 100vh;

    display: flex;
    flex-wrap: nowrap;
    align-content: center;
    justify-content: center;
    align-items: center;

    div.Site { 
      width: 33.33vw;
      height: 100vh;
      color: white;
      background-color: #263238;
    }
  }
</style>

<style>
  body, html {
    height: 100%;
    margin: 0;
    padding: 0;
    box-sizing: content-box;
  }

  * {
    box-sizing: content-box;
  }
</style>
