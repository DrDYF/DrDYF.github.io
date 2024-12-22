// 获取访问次数
let visitCount = localStorage.getItem('visitCount');
// 如果没有设置，初始化为0
if (!visitCount) {
    visitCount = 0;
}
// 增加访问次数
visitCount++;
// 将更新后的值保存到 localStorage
localStorage.setItem('visitCount', visitCount);
// 显示访问次数
document.getElementById('visit-count').innerText = `你第 ${visitCount} 次来啦`;
