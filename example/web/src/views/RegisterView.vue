<template>
  <div class="login">
    <h1 class="">数学题目自动生成系统账号注册</h1>
    <Register/>
  </div>
</template>
<script>
// @ is an alias to /src

import Register from '@/components/Register.vue'

export default {
  name: 'RegisterView',
  components: {
      Register
  }
}
</script>