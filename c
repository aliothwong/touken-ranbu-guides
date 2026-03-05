# 限锻保底计算器

输入您当前拥有的资源和御札，计算器会自动计算还需要多少资源才能达到保底（5000积分）。

---

<html>
<head>
<style>
body { font-family: Arial, sans-serif; padding: 20px; background-color: #f5f5f5; }
.container { max-width: 800px; margin: 0 auto; background-color: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }
h2 { color: #333; }
.section { margin: 20px 0; padding: 15px; background-color: #f9f9f9; border-left: 4px solid #007bff; }
.input-group { margin: 10px 0; display: flex; align-items: center; gap: 10px; }
label { width: 150px; font-weight: bold; }
input { padding: 8px; border: 1px solid #ddd; border-radius: 4px; width: 100px; }
button { padding: 10px 20px; background-color: #28a745; color: white; border: none; border-radius: 4px; cursor: pointer; font-size: 16px; }
button:hover { background-color: #218838; }
.result { margin-top: 20px; padding: 15px; background-color: #e7f3ff; border: 2px solid #007bff; border-radius: 4px; }
.result h3 { color: #007bff; margin-top: 0; }
.result-item { margin: 8px 0; font-size: 16px; }
.warning { color: #d9534f; font-weight: bold; }
.success { color: #5cb85c; font-weight: bold; }
table { width: 100%; margin-top: 10px; border-collapse: collapse; }
table th, table td { padding: 8px; text-align: left; border: 1px solid #ddd; }
table th { background-color: #007bff; color: white; }
</style>
</head>
<body>

<div class="container">
  <h1>限锻保底计算器</h1>
  
  <div class="section">
    <h2>📊 当前资源</h2>
    
    <div class="input-group">
      <label>木炭数量：</label>
      <input type="number" id="charcoal" value="0" min="0">
    </div>
    
    <div class="input-group">
      <label>玉刚数量：</label>
      <input type="number" id="jade" value="0" min="0">
    </div>
    
    <div class="input-group">
      <label>冷却材数量：</label>
      <input type="number" id="coolant" value="0" min="0">
    </div>
    
    <div class="input-group">
      <label>砥石数量：</label>
      <input type="number" id="whetstone" value="0" min="0">
    </div>
  </div>

  <div class="section">
    <h2>🎫 当前御札</h2>
    
    <div class="input-group">
      <label>梅御札数量：</label>
      <input type="number" id="mei" value="0" min="0">
      <span>（每次10积分）</span>
    </div>
    
    <div class="input-group">
      <label>竹御札数量：</label>
      <input type="number" id="take" value="0" min="0">
      <span>（每次15积分）</span>
    </div>
    
    <div class="input-group">
      <label>松御札数量：</label>
      <input type="number" id="matsu" value="0" min="0">
      <span>（每次20积分）</span>
    </div>
    
    <div class="input-group">
      <label>富士御札数量：</label>
      <input type="number" id="fuji" value="0" min="0">
      <span>（每次60积分）</span>
    </div>
  </div>

  <button onclick="calculate()">📈 开始计算</button>

  <div id="result"></div>
</div>

<script>
function calculate() {
  // 输入数据
  const charcoal = parseInt(document.getElementById("charcoal").value) || 0;
  const jade = parseInt(document.getElementById("jade").value) || 0;
  const coolant = parseInt(document.getElementById("coolant").value) || 0;
  const whetstone = parseInt(document.getElementById("whetstone").value) || 0;
  
  const mei = parseInt(document.getElementById("mei").value) || 0;
  const take = parseInt(document.getElementById("take").value) || 0;
  const matsu = parseInt(document.getElementById("matsu").value) || 0;
  const fuji = parseInt(document.getElementById("fuji").value) || 0;

  // 计算当前总积分
  let currentPoints = 0;
  let resourcesUsed = 0;

  // 计算御札能提供的积分
  const meiPoints = mei * 10;
  const takePoints = take * 15;
  const matsuPoints = matsu * 20;
  const fujiPoints = fuji * 60;
  
  currentPoints = meiPoints + takePoints + matsuPoints + fujiPoints;
  resourcesUsed = (mei + take + matsu + fuji) * 700;

  // 目标积分
  const targetPoints = 5000;
  const pointsNeeded = Math.max(0, targetPoints - currentPoints);

  // 需要多少次普通锻刀（5积分/次，700资源/次）
  const normalForgesNeeded = Math.ceil(pointsNeeded / 5);
  const resourcesNeededForNormal = normalForgesNeeded * 700;

  // 总资源需求
  const totalResourcesNeeded = resourcesUsed + resourcesNeededForNormal;
  const totalResourcesAvailable = charcoal + jade + coolant + whetstone;
  const resourcesShortage = Math.max(0, totalResourcesNeeded - totalResourcesAvailable);

  // 生成结果
  let resultHTML = '<div class="result"><h3>📋 计算结果</h3>';
  
  resultHTML += `
    <table>
      <tr>
        <th>项目</th>
        <th>数值</th>
      </tr>
      <tr>
        <td>当前拥有积分</td>
        <td><strong>${currentPoints} / 5000</strong></td>
      </tr>
      <tr>
        <td>还需积分</td>
        <td><strong>${pointsNeeded}</strong></td>
      </tr>
      <tr>
        <td>需要普通锻刀次数</td>
        <td><strong>${normalForgesNeeded}</strong></td>
      </tr>
    </table>
  `;

  resultHTML += '<h4 style="margin-top: 15px;">💰 资源计算</h4>';
  resultHTML += `
    <table>
      <tr>
        <th>资源类型</th>
        <th>已有</th>
        <th>需要</th>
        <th>状态</th>
      </tr>
      <tr>
        <td>总资源</td>
        <td>${totalResourcesAvailable}</td>
        <td>${totalResourcesNeeded}</td>
        <td>${resourcesShortage === 0 ? '<span class="success">✅ 足够</span>' : '<span class="warning">❌ 不足 ' + resourcesShortage + '</span>'}</td>
      </tr>
    </table>
  `;

  resultHTML += '<h4 style="margin-top: 15px;">📊 详细分析</h4>';
  resultHTML += `
    <div class="result-item">✓ 梅御札：${mei} 张 → ${meiPoints} 积分</div>
    <div class="result-item">✓ 竹御札：${take} 张 → ${takePoints} 积分</div>
    <div class="result-item">✓ 松御札：${matsu} 张 → ${matsuPoints} 积分</div>
    <div class="result-item">✓ 富士御札：${fuji} 张 → ${fujiPoints} 积分</div>
    <div class="result-item">✓ 御札锻刀资源：${resourcesUsed}</div>
    <div class="result-item">✓ 普通锻刀资源：${resourcesNeededForNormal}</div>
  `;

  if (resourcesShortage > 0) {
    resultHTML += `
      <div class="result-item" style="margin-top: 10px;">
        <span class="warning">⚠️ 资源不足 ${resourcesShortage}，需要继续攒资源！</span>
      </div>
    `;
  } else {
    resultHTML += `
      <div class="result-item" style="margin-top: 10px;">
        <span class="success">✅ 资源充足！可以完成保底！</span>
      </div>
    `;
  }

  resultHTML += '</div>';
  document.getElementById("result").innerHTML = resultHTML;
}

// 页面加载时自动计算一次
window.onload = function() {
  calculate();
};
</script>

</body>
</html>

---

## 使用说明

1. **输入您当前拥有的资源数量**（木炭、玉刚、冷却材、砥石）
2. **输入您当前拥有的各项御札数量**
3. **点击"开始计算"** 按钮
4. 计算器会显示：
   - 当前积分进度
   - 还需多少积分
   - 还需多少次锻刀
   - 资源是否充足

---

返回 [[目录|目录]]