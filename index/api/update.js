// index/api/update.js

let latestData = { flow: 0, total: 0 };  // Initialize the data

// Handle POST request from Arduino
export default function handler(req, res) {
  if (req.method === 'POST') {
    const { flow, total } = req.body;

    // Validate the incoming data to ensure it's a number
    if (!isNaN(flow) && !isNaN(total)) {
      // Update the latestData object correctly with the received data
      latestData = { flow, total };
      console.log("✅ Received and updated data:", latestData);  // Log the updated data to confirm

      return res.status(200).json({ message: "Data updated successfully" });
    }

    // If the data is invalid, send a bad request response
    return res.status(400).json({ message: "Invalid data" });
  }

  // If the method is not POST, send Method Not Allowed
  return res.status(405).json({ message: "Only POST allowed" });
}

// Export latestData to make it accessible to other files like data.js
export { latestData };
