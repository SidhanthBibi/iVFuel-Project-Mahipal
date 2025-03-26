import { redis } from "@/lib/redis";

export default async function handler(req, res) {
  if (req.method !== "POST") {
    return res.status(405).json({ message: "Only POST allowed" });
  }

  try {
    const { flow, total } = req.body;

    if (isNaN(flow) || isNaN(total)) {
      return res.status(400).json({ message: "Invalid data" });
    }

    await redis.set("flow", flow);
    await redis.set("total", total);

    console.log("✅ Received and updated data:", { flow, total });
    res.status(200).json({ message: "Stored successfully" });
  } catch (err) {
    console.error("❌ Error in POST:", err);
    res.status(500).json({ message: "Internal server error" });
  }
}
