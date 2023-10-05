<template>
  <h3>请选择题目生成的难度</h3><br>
  <input type="radio" v-model="grade" value="小学">小学<br><br>
  <input type="radio" v-model="grade" value="初中">初中<br><br>
  <input type="radio" v-model="grade" value="高中">高中<br><br>
 题目难度： {{ grade }}
  <h3>请刷入题目生成的数目</h3><br>
  <input type="number" v-model="num" oninput="value=value.replace(/[^\d]/g,'')"><br><br>
  注：仅支持正整数,题目数目必须大于等于10且小于等于30<br>
  <br><br><button @click="get_problem()">生成题目</button><br>
  
</template>

<script>
import axios from 'axios'
import { initCustomFormatter } from 'vue';
export default (await import('vue')).defineComponent({
  data() {
    return {
      grade:null,
      num:null,
    }
  },
  mounted: function(){
    this.init();
  },
  methods: {
    init(){
      this.grade=null;
      this.num=null;
    },
    get_problem() {
      if(this.grade==null){
        alert("请选择题目难度")
      }else if(this.num<10||this.num>30) {
        alert("题目数目不符合要求请重新输入")
      }
      else {
        var returnData = {
          type:this.grade,
          num:this.num,
          account:this.$store.state.account
        }
        //alert(JSON.stringify(returnData));
        axios.defaults.headers.post["Content-type"]="application/json";
        axios
          .post("http://localhost:8000/produce-paper",JSON.stringify(returnData))
          .then((res)=>{
            if(res.data.success == false){发送题目信息,获取返回
              alert("生成题目失败，请重新生成");
            }else {//
              this.$store.state.grade=this.grade;
              this.$store.state.num=this.num;
              this.$router.push("/problem");
            }
        })
      }
    }
  },
})
</script>