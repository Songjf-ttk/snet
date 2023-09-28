<template>
  <div class="edit_password">
    <h1 class="">{{ this.$store.state.username }}&#8195密码修改</h1>
    <EditPassword/>
  </div>
</template>

<script>
// @ is an alias to /src

import EditPassword from '@/components/EditPassword.vue';

export default {
  name: 'EditPasswordView',
  components: {
    EditPassword
  },
  mounted:function(){
    this.init();
  },
  methods: {
    init(){
      if(this.$store.state.islogin==false) {
        alert("您还没有登录，点击确定返回登录界面");
        this.$router.push('/');
      }
    }
  }
}
</script>