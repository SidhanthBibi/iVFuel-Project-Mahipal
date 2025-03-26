import { redis } from "@/lib/redis";

export default async function handler(req, res) {
  if (req.method === "POST") {
    const { flow, total } = req.body;

    if (!isNaN(flow) && !isNaN(total)) {
      await redis.set("flow", flow);
      await redis.set("total", total);
      console.log("✅ Updated Redis:", { flow, total });
      return res.status(200).json({ message: "Stored successfully" });
    }

    return res.status(400).json({ message: "Invalid data" });
  }

  return res.status(405).json({ message: "Only POST allowed" });
}
