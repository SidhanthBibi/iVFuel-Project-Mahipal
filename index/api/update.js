// index/api/update.js

let latestData = { flow: 0, total: 0 };  // Initial state, with flow and total set to 0

// Handle POST request from Arduino
export default function handler(req, res) {
  if (req.method === 'POST') {
    const { flow, total } = req.body;

    // Validate the incoming data to ensure it's a number
    if (!isNaN(flow) && !isNaN(total)) {
      latestData = { flow, total };  // Update the latestData with the new flow and total values
      console.log("✅ Received data: ", latestData);  // Log the received data to confirm it's being updated
      return res.status(200).json({ message: "Data updated successfully" });
    }

    return res.status(400).json({ message: "Invalid data" });
  }

  return res.status(405).json({ message: "Only POST allowed" });
}

// Export latestData to make it accessible to other files
export { latestData };

// In this snippet, the latestData object is initialized with flow and total properties set to 0. The handler function listens for POST requests and updates the latestData object with the new flow and total values received in the request body. The updated data is then logged to the console for confirmation. The latestData object is exported to make it accessible to other files, such as the data.js file that serves the latest data to clients. This separation of concerns allows for a clear distinction between updating and serving data, making the code more modular and maintainable.