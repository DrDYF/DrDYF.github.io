const nodemailer = require('nodemailer');

module.exports = async (req, res) => {
  // 处理跨域
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Access-Control-Allow-Methods', 'POST');
  
  if (req.method === 'OPTIONS') return res.status(200).end();

  try {
    const { imageData, toEmail } = JSON.parse(req.body);
    
    // 邮件配置（使用环境变量）
    const transporter = nodemailer.createTransport({
      host: 'smtp.163.com',
      port: 465,
      secure: true,
      auth: {
        user: process.env.EMAIL_USER,  // 正确变量名
        pass: process.env.EMAIL_PASS   // 正确变量名
      }
    });

    // 发送邮件
    await transporter.sendMail({
      from: `"自动拍照系统" <${process.env.EMAIL_USER}>`,  // 统一使用环境变量
      to: toEmail,
      subject: '自动拍摄的照片',
      html: '<p>系统自动发送的照片：</p>',
      attachments: [{
        filename: 'photo.jpg',
        content: imageData.split('base64,')[1],
        encoding: 'base64'
      }]
    });

    res.status(200).json({ success: true });
  } catch (error) {
    console.error('发送失败:', error);
    res.status(500).json({ error: '发送失败' });
  }
};
