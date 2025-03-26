// index/api/update.js
export default async function handler(req, res) {
    if (req.method === 'POST') {
      const { flow, total } = req.body;
  
      console.log("💧 Flow:", flow);
      console.log("📦 Total:", total);
  
      // You could store this in a DB or cache it
      return res.status(200).json({ message: "Received!" });
    }
  
    res.status(405).json({ message: "Only POST allowed" });
  }
  