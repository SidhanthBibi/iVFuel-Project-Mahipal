// index/api/update.js

let latestData = { flow: 0, total: 0 };  // initial state

// Handle POST request from Arduino
export default function handler(req, res) {
  if (req.method === 'POST') {
    const { flow, total } = req.body;

    // Validate the incoming data to ensure it's a number
    if (!isNaN(flow) && !isNaN(total)) {
      // Update the latestData object correctly
      latestData = { flow, total };
      console.log("✅ Received and updated data: ", latestData);  // Log the received data

      return res.status(200).json({ message: "Data updated successfully" });
    }

    return res.status(400).json({ message: "Invalid data" });
  }

  return res.status(405).json({ message: "Only POST allowed" });
}

export { latestData };  // Ensure latestData is being exported
